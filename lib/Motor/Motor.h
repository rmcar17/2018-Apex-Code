#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Pins.h>

class Motor {
  public:
    Motor(){}
    Motor(int pwm, int drv, int brk, bool rev);
    void motorSetup();
    void move(int speed);
  private:
    int pwmPin, drvPin, brkPin;
    bool reversed;
};

#endif
