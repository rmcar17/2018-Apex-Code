#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Pins.h>

class Motor {
  public:
    Motor(){}
    Motor(int pwm, int inOne, int inTwo);
    void MotorSetup();
    void move(int speed);
  private:
    int pwmPin, inOnePin, inTwoPin;
};

#endif
