#include "Motor.h"

Motor::Motor(int pwm, int inOne, int inTwo, int motorAngle,int standby) {
  pwmPin = pwm;
  inOnePin = inOne;
  inTwoPin = inTwo;
}

void Motor::MotorSetup()
{
  pinMode(pwmPin, OUTPUT);
  pinMode(inOnePin, OUTPUT);
  pinMode(inTwoPin, OUTPUT);
}

void Motor::move(int speed){
    if(speed>0)
    {
      analogWrite(pwmPin,constrain(speed,0,255));
      digitalWrite(inOnePin,HIGH);
      digitalWrite(inTwoPin,LOW);
    }
    else if(speed<0)
    {
      analogWrite(pwmPin,constrain(abs(speed),0,255));
      digitalWrite(inOnePin,LOW);
      digitalWrite(inTwoPin,HIGH);
    }
    else
    {
      analogWrite(pwmPin, 255);
      digitalWrite(inOnePin, LOW);
      digitalWrite(inTwoPin, LOW);
    }
}
