#include <Arduino.h>
#include <Timer.h>
#include <Pins.h>
#include <Defines.h>

Timer kickInterval = Timer(KICK_INTERVAL);
Timer kickLow = Timer(KICK_HIGH_TIME);

void setup() {
  pinMode(KICKER_PIN, OUTPUT);
  digitalWrite(KICKER_PIN, LOW);
}

void loop() {
  if(kickInterval.hasTimePassed()){
    digitalWrite(KICKER_PIN, HIGH);
    kickLow.update();
  }
  if(kickLow.hasTimePassed()){
    digitalWrite(KICKER_PIN, LOW);
  }
}
