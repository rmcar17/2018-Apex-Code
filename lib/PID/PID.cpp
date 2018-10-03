#include "PID.h"

PID::PID(double p, double i, double d){
  kp = p;
  ki = i;
  kd = d;

  integral = 0;
  previousTime = micros();
  previousInput = 0;
}

double PID::update(double error){
  double derivative;

  unsigned long currentTime = micros();
  double elapsedTime = (currentTime - previousTime) / 1000000.0;
  previousTime = currentTime;

  integral += error * elapsedTime;

  derivative = (error - previousInput) / elapsedTime;
  previousInput = error;

  double correction = kp * error + ki * integral + kd * derivative;

  return correction;
}
