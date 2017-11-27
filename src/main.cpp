#include <Arduino.h>

#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

#include <MotorController.h>
#include <Motor.h>

#include <PixyI2C.h>
#include <Compass.h>

PixyI2C pixy;
Compass comp;

MotorController motors;

int compassCorrect();

void setup() {
  Wire.begin();
  comp.compassSetup();

  motors.motorSetup();
  motors.brake();

  comp.calibrate();
}

void loop() {
  comp.updateGyro();

  motors.rotate(compassCorrect());
}

int compassCorrect(){
  int correction = 360-comp.heading;

  correction = correction<180 ? -correction:360-correction;
  correction *= 5;

  return correction;
}
