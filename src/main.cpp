#include <Arduino.h>

#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

#include <MotorController.h>
#include <Motor.h>

#include <Compass.h>

MotorController motors;

void setup() {
  motors.motorSetup();
}

void loop() {
  motors.moveDirection(315, 255, 0);
}
