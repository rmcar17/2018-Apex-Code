#include "TSOPController.h"

TSOPController::TSOPController(){
}

void TSOPController::TSOPSetup(){
  pinMode(TSOP_POWER,OUTPUT);

  for(int tsop=0;tsop<TSOP_NUM;tsop++)
  {
    pinMode(sensors[tsop],INPUT_PULLUP);
  }

  digitalWrite(TSOP_POWER, HIGH);
}

void TSOPController::read(){
  int sensors[TSOP_NUM] = {TSOP_1, TSOP_2, TSOP_3, TSOP_4, TSOP_5, TSOP_6, TSOP_7, TSOP_8, TSOP_9, TSOP_10, TSOP_11, TSOP_12};
  for(int i=0;i<READ_NUM;i++)
  {
    for(int tsop=0;tsop<TSOP_NUM;tsop++)
    {
      values[tsop] += digitalRead(sensors[tsop]) ^ 1;
    }
  }

  #if DEBUG_TSOPS
    for(int tsop=0;tsop<TSOP_NUM;tsop++){
      Serial.print(" TSOP");
      Serial.print(tsop+1);
      Serial.print(": ");
      Serial.print(values[tsop]);
    }
    Serial.println();
  #endif
}

void TSOPController::refresh(){
  digitalWrite(TSOP_POWER, LOW);
  delay(TSOP_DELAY);
  digitalWrite(TSOP_POWER, HIGH);
}

BallData TSOPController::getBallData(){
  refresh();
  read();
  filterValues();
  errorCorrect();
  sortValues();

  strAng = getStrAng(TSOP_N);

  reset();
  return strAng;
}

void TSOPController::filterValues(){
  for(int tsop=0;tsop<TSOP_NUM;tsop++)
  {
    if(values[tsop]<MIN_IGNORE_TSOP||values[tsop]>MAX_IGNORE_TSOP)
    {
      values[tsop] = 0;
    }
  }
}

void TSOPController::errorCorrect(){
  for(int tsop=0;tsop<TSOP_NUM;tsop++){
    if(values[tsop]==0 && values[tsop-1]!=0 && values[mod(tsop+1,TSOP_NUM)]){
      values[tsop] = round((values[tsop-1]+values[mod(tsop+1,TSOP_NUM)])/2);
    }
  }
}

void TSOPController::sortValues(){
  for(int j=0;j<TSOP_NUM;j++)
  {
    m_strength = -1;
    m_index = 0;
    for(int i=0;i<TSOP_NUM;i++)
    {
      if(values[i]>m_strength)
      {
        m_strength = values[i];
        m_index = i;
      }
    }
    values[m_index] = 0;
    finalValues[j] = m_strength;
    finalAngles[j] = angles[m_index];
  }
}

void TSOPController::reset(){
  values[TSOP_NUM] = {0};
  finalValues[TSOP_NUM] = {0};
  finalAngles[TSOP_NUM] = {0};
}

int TSOPController::getStr(int Str_n){
  int returnStrength = 0;
  for(int i=0;i<Str_n;i++){
    returnStrength += finalValues[i];
  }
  returnStrength = round(returnStrength/Str_n);
  return returnStrength;
}

BallData TSOPController::getStrAng(int best_n){
  int returnAngle = 0;
  int returnStrength = 0;
  double i=0,j=0;
  for(int n=0;n<best_n;n++){
    i += (double)finalValues[n]*sin(toRadians((double)finalAngles[n]));
    j += (double)finalValues[n]*cos(toRadians((double)finalAngles[n]));
  }
  if(i==0){
      if(j==0){
        returnAngle = -1;
      }
      else if(j>0){
        returnAngle = 0;
      }
      else{
        returnAngle = 180;
      }
  }
  else{
    returnAngle = 360-(int)mod(270+(int)round(toDegrees(atan2(j,i))),360);
  }
  returnStrength = getStr(TSOP_S);
  return {returnStrength,returnAngle};
}
