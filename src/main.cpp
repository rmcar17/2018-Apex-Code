#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <TSOPController.h>
#include <Compass.h>
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

Compass comp;
TSOPController tsops;

MotorController motors;

Orbit orbit;

PlayMode role;

BallData ball;
GoalData goal;
MoveData move;

void setup() {
  #if DEBUG_ANY
  Serial.begin(9600);
  #endif

  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  motors.motorSetup();
  motors.brake();


  tsops.TSOPSetup();

  orbit.resetAllData();


  role = PlayMode::attacker;

  goal.angle = -1;
  goal.distance = 0;
  goal.visible = false;
}

void loop() {
  comp.updateGyro();

  //Create another class which fetches
  //goal data which takes an input of
  //the robot's current role

  //Create another class which checks
  //whether the robots should switch
  //roles
  ball = tsops.getBallData();

  orbit.setRole(role);
  orbit.setGoalData(goal);
  orbit.setBallData(ball);
  orbit.setCompAngle(comp.getHeading());

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();

  motors.moveDirection(move);

  orbit.resetAllData();
}
