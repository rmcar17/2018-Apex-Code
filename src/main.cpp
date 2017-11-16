#include <Arduino.h>

#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

#include <MotorController.h>
#include <Motor.h>

MotorController motors;

void setup() {
  Serial.begin(9600);
  motors.motorSetup();
}

void loop() {
  motors.moveDirection(230, 255, 0);
}
