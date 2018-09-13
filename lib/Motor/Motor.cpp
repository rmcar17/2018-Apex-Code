#include "Motor.h"

Motor::Motor(int pwm, int dir, int brk, bool rev) {
  pwmPin = pwm;
  dirPin = dir;
  brkPin = brk;
  reversed = rev;
}

void Motor::motorSetup()
{
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(brkPin, OUTPUT);
  analogWriteFrequency(pwmPin,93750);// 19000);
}

void Motor::move(int speed){
    if(speed>0)
    {
      analogWrite(pwmPin, constrain(speed,0,255));
      digitalWrite(dirPin, !reversed ? HIGH : LOW);
      digitalWrite(brkPin, LOW);
    }
    else if(speed<0)
    {
      analogWrite(pwmPin,constrain(abs(speed),0,255));
      digitalWrite(dirPin, !reversed ? LOW : HIGH);
      digitalWrite(brkPin,LOW);
    }
    else
    {
      analogWrite(pwmPin, 0);
      digitalWrite(brkPin, LOW);
    }
}
