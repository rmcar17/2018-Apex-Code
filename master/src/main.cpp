#include <Arduino.h>
#include <Kicker.h>

Kicker kicker;

void setup() {
  kicker.setup();
}

void loop() {
  kicker.kick();
  kicker.resetKicker();
}
