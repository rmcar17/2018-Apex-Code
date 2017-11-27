#ifndef PID_H_
#define PID_H_

#include <Arduino.h>
#include <defines.h>

class PID {
  public:
    double kp, ki, kd;

    PID(double p, double i, double d);
    double update(double error);

  private:
    unsigned long previousTime;
    double previousInput;
    double integral;
};

#endif
