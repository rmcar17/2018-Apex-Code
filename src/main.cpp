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

Orbit orbit;

BallData ball;
MoveData move;

int mockAngle;
int mockDistance;
int mockRotation;

void setup() {
  if(DEBUG_ANY){
    Serial.begin(9600);
  }

  Wire.begin();
  comp.compassSetup();

  motors.motorSetup();
  motors.brake();

  orbit.resetMoveData();

  comp.calibrate();

  mockAngle = 0;
  mockDistance = 160;
  mockRotation = -1;

  ball.angle = mockAngle;
  ball.distance = mockDistance;
}

void loop() {
  comp.updateGyro();

  orbit.calculateMoveData(ball);
  orbit.calculateRotation(comp.heading, mockRotation);

  move = orbit.getMoveData();

  motors.moveDirection(move);

  orbit.resetMoveData();
}
