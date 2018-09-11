#ifndef LIGHT_GATE_H
#define LIGHT_GATE_H

#include <Arduino.h>
#include <Defines.h>
#include <Pins.h>

class LightGate {
  public:
    LightGate();

    void setup();
    bool hasBall();
  private:
    void read();
    int readVal;
};

#endif
