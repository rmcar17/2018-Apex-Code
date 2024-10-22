#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
  public:
    Timer(unsigned int timeLength);

    void update();
    bool hasTimePassed();
    bool hasTimePassedNoUpdate();
  private:
    unsigned int duration, startTime;
};
#endif
