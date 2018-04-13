#include "Motor.h"

Motor::Motor(int pwm, int drv, int brk, bool rev) {
  pwmPin = pwm;
  drvPin = drv;
  brkPin = brk;
  reversed = rev;
}

void Motor::motorSetup()
{
  pinMode(pwmPin, OUTPUT);
  pinMode(drvPin, OUTPUT);
  pinMode(brkPin, OUTPUT);
  analogWriteFrequency(pwmPin, 19000);
}

void Motor::move(int speed){
    if(speed>0)
    {
      analogWrite(pwmPin, constrain(speed,0,255));
      digitalWrite(drvPin, !reversed ? HIGH : LOW);
      digitalWrite(brkPin, LOW);
    }
    else if(speed<0)
    {
      analogWrite(pwmPin,constrain(abs(speed),0,255));
      digitalWrite(drvPin, !reversed ? LOW : HIGH);
      digitalWrite(brkPin,LOW);
    }
    else
    {
      analogWrite(pwmPin, 0);
      digitalWrite(drvPin, LOW);
      digitalWrite(brkPin, HIGH);
    }
}
