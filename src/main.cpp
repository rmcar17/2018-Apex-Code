#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
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
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;
Orbit orbit;

PlayMode role;

MoveData move;

void setup() {
  #if DEBUG_ANY
    Serial.begin(38400);
  #endif
  camera.setup();

  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  motors.motorSetup();
  motors.brake();

  lights.setup();

  orbit.resetAllData();

  role = PlayMode::attack;
}

void loop() {
  comp.updateGyro();
  //Create another class which checks
  //whether the robots should switch
  //roles
  // camera.update();
  // camera.calculateEntities();

  orbit.setRole(role);
  orbit.setGoalData(camera.getAttackGoal(), camera.getDefendGoal());
  orbit.setBallData(camera.getBall());
  orbit.setCompAngle(comp.getHeading());

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();

  motors.moveDirection({-1,MAX_SPEED,move.rotation});

  orbit.resetAllData();
}
