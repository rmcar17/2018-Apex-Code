#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Orbit.h>
#include <Lidar.h>
#include <Camera.h>
#include <CameraController.h>
#include <RoleController.h>
#include <Timer.h>
#include <PID.h>
#include <Common.h>
#include <Vector.h>
#include <Role.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;
Orbit orbit;

Role role;

MoveData move;

void setup() {
  pinMode(TEENSY_LED, OUTPUT);

  #if DEBUG_ANY
    Serial.begin(38400);
  #endif
  camera.setup();

  digitalWrite(TEENSY_LED, HIGH);

  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  motors.motorSetup();
  motors.brake();

  orbit.resetAllData();

  role = Role::attack;

  digitalWrite(TEENSY_LED, LOW);
}

void loop() {
  // motors.moveDirection({0,100,0});
  comp.updateGyro();

  camera.update();

  orbit.setRole(role);
  orbit.setGoalData(camera.getAttackGoal(), camera.getDefendGoal());
  orbit.setBallData(camera.getBall());
  orbit.setCompAngle(comp.getHeading());

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();
  // move.angle = -1;
  motors.moveDirection(move);
  // motors.moveDirection({0,100,0});
  orbit.resetAllData();
}
