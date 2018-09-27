#include <Arduino.h>
#include <Kicker.h>
#include <LightGate.h>

Kicker kicker;
LightGate lg;

void setup() {
  lg.setup();
  kicker.setup();
}

void loop() {
  if(lg.hasBall()){
    kicker.kick();
  }
  kicker.resetKicker();
}
