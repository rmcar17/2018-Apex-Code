#ifndef KICKER_H
#define KICKER_H

#include <Arduino.h>
#include <Timer.h>
#include <Defines.h>
#include <Pins.h>

class Kicker{
  public:
    Kicker();

    void setup();

    void kick();
    void resetKicker();
  private:
    Timer kickInterval = Timer(KICK_INTERVAL);
    Timer kickLow = Timer(KICK_HIGH_TIME);
};

#endif
