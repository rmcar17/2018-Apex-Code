#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <TSOPController.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Orbit.h>
#include <Camera.h>
#include <CameraController.h>
#include <PID.h>
#include <Common.h>
#include <Vector.h>
#include <PlayMode.h>
#include <EntityData.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

Compass comp;
TSOPController tsops;

Camera camera;

MotorController motors;

LightSensorController lights;
Orbit orbit;

PlayMode role;

EntityData ball;
EntityData goal;
MoveData move;

void setup() {
  #if DEBUG_ANY
    Serial.begin(38400);
  #endif
  camera.setup();
  // Wire.begin();
  // comp.compassSetup();
  // comp.calibrate();
  //
  // motors.motorSetup();
  // motors.brake();
  //
  // lights.setup();
  //
  // tsops.TSOPSetup();
  //
  // orbit.resetAllData();
  //
  //
  // role = PlayMode::attacker;
  //
  // goal.angle = -1;
  // goal.distance = 0.0;
  // goal.visible = false;
}

void loop() {
  camera.update();
  // comp.updateGyro();
  //
  // //Create another class which fetches
  // //goal data which takes an input of
  // //the robot's current role
  //
  // //Create another class which checks
  // //whether the robots should switch
  // //roles
  // ball = tsops.getBallData();
  //
  // orbit.setRole(role);
  // orbit.setGoalData(goal);
  // orbit.setBallData(ball);
  // orbit.setCompAngle(comp.getHeading());
  //
  // orbit.calculateMoveData();
  // orbit.calculateRotation();
  //
  // move = orbit.getMoveData();
  //
  // motors.moveDirection(move);
  //
  // orbit.resetAllData();
}
