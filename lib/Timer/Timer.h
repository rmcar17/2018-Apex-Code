#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
  public:
    Timer(unsigned long int timeLength);

    void update();
    bool hasTimePassed();
  private:
    unsigned long int duration, startTime;
};
#endif
