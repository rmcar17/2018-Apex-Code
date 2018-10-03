#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Pins.h>

class Motor {
  public:
    Motor(){}
    Motor(int pwm, int dir, int brk, bool rev);
    void motorSetup();
    void move(int speed);
    void brake();
  private:
    int pwmPin, dirPin, brkPin;
    bool reversed;
};

#endif
