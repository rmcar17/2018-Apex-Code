#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <TSOPController.h>
#include <Compass.h>
#include <PixyI2C.h>
#include <Orbit.h>
#include <PID.h>
#include <Common.h>
#include <PlayMode.h>
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

PlayMode role;

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
  #if DEBUG_ANY
    Serial.begin(9600);
  #endif

  Wire.begin();
  comp.compassSetup();

  motors.motorSetup();
  motors.brake();

  orbit.resetAllData();

  comp.calibrate();

  role = PlayMode::attacker;

  mockBallAngle = 360-SMALL_ORBIT+1;
  mockBallDistance = CLOSE_ORBIT-10;
  mockBallVisible = false;

  mockGoalAngle = 0;
  mockGoalDistance = 9;
  mockGoalVisible = true;

  ball.angle = mockBallAngle;
  ball.distance = mockBallDistance;
  ball.visible = mockBallVisible;

  goal.angle = mockGoalAngle;
  goal.distance = mockGoalDistance;
  goal.visible = mockGoalVisible;
}

void loop() {
  comp.updateGyro();

  //Create another class which fetches
  //goal data which takes an input of
  //the robot's current role

  //Create another class which checks
  //whether the robots should switch
  //roles

  orbit.setRole(role);
  orbit.setGoalData(goal);
  orbit.setBallData(ball);
  orbit.setCompAngle(0);//comp.getHeading());

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();

  motors.moveDirection(move);

  orbit.resetAllData();

  #if DEBUG_ANY
    delay(100);
  #endif
}
