#include "Motor.h"

Motor::Motor(int pwm, int drv, int brk) {
  pwmPin = pwm;
  drvPin = drv;
  brkPin = brk;
}

void Motor::motorSetup()
{
  pinMode(pwmPin, OUTPUT);
  pinMode(drvPin, OUTPUT);
  pinMode(brkPin, OUTPUT);
}

void Motor::move(int speed){
    if(speed>0)
    {
      analogWrite(pwmPin,constrain(speed,0,255));
      digitalWrite(drvPin,HIGH);
      digitalWrite(brkPin,LOW);
    }
    else if(speed<0)
    {
      analogWrite(pwmPin,constrain(abs(speed),0,255));
      digitalWrite(drvPin,LOW);
      digitalWrite(brkPin,HIGH);
    }
    else
    {
      analogWrite(pwmPin, 0);
      digitalWrite(drvPin, LOW);
      digitalWrite(brkPin, HIGH);
    }
}
