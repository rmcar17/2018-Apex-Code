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
#include <GoalData.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

PixyI2C pixy;
Compass comp;

MotorController motors;

Orbit orbit;

BallData ball;
GoalData goal;
MoveData move;

int mockBallAngle;
int mockBallDistance;
bool mockBallVisible;

int mockGoalAngle;
int mockGoalDistance;
bool mockGoalVisible;

void setup() {
  if(DEBUG_ANY){
    Serial.begin(9600);
  }

  Wire.begin();
  comp.compassSetup();

  motors.motorSetup();
  motors.brake();

  orbit.resetAllData();

  comp.calibrate();

  mockBallAngle = 0;
  mockBallDistance = 160;
  mockBallVisible = true;

  mockGoalAngle = 0;
  mockGoalDistance = 10;
  mockGoalVisible = false;

  ball.angle = mockBallAngle;
  ball.distance = mockBallDistance;
  ball.visible = mockBallVisible;

  goal.angle = mockGoalAngle;
  goal.distance = mockGoalDistance;
  goal.visible = mockGoalVisible;
}

void loop() {
  comp.updateGyro();

  orbit.setGoalData(goal);
  orbit.setBallData(ball);
  orbit.setCompAngle(comp.heading);

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();

  motors.moveDirection(move);

  orbit.resetAllData();
}
