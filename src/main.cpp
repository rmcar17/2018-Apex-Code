#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <TSOPController.h>
#include <Compass.h>
#include <PixyI2C.h>
#include <Orbit.h>
#include <PID.h>
#include <Common.h>
#include <BallData.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

PixyI2C pixy;
Compass comp;

MotorController motors;

PID compCorrect = PID(COMPASS_KP, COMPASS_KI, COMPASS_KD);

int compassCorrect();

void setup() {
  if(DEBUG_ANY){
    Serial.begin(9600);
  }

  Wire.begin();
  comp.compassSetup();

  motors.motorSetup();
  motors.brake();

  comp.calibrate();
}

void loop() {
  comp.updateGyro();

  motors.rotate(compCorrect.update(comp.heading < 180 ? comp.heading : -(360-comp.heading)));
}

int compassCorrect(){
  int correction = 360-comp.heading;

  correction = correction<180 ? -correction:360-correction;
  correction *= 5;

  return correction;
}
