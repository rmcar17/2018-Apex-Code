#include <Arduino.h>
#include <Kicker.h>
#include <LightGate.h>
#include <MotorController.h>

MotorController motors;

Kicker kicker;
LightGate lg;

void setup() {
  motors.motorSetup();
  motors.brake();
  
  lg.setup();
  kicker.setup();
}

void loop() {
  if(lg.hasBall()){
    kicker.kick();
  }
  kicker.resetKicker();

  motors.moveDirection({0,100,0});
}
