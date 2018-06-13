#include <LightGate.h>

LightGate::LightGate(){

}

void LightGate::setup(){
  pinMode(LIGHT_GATE_PIN, INPUT);
}

void LightGate::read(){
  readVal = analogRead(LIGHT_GATE_PIN);
  Serial.println(readVal);
}

bool LightGate::hasBall(){
  read();
  return readVal < LIGHT_GATE_THRESH;
}
