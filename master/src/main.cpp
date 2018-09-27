#include <Arduino.h>
#include <Kicker.h>
#include <LightGate.h>
#include <MotorController.h>

MotorController motors;

Kicker kicker;
LightGate lg;

void setup() {
  motors.motorSetup();
  motors.brake();

  orbit.setup();
  orbit.resetAllData();

  lidars.setup();

  role = Role::attack;

  digitalWrite(TEENSY_LED,LOW);
}

void loop() {
  // Compass
  comp.updateGyro();
  int heading = comp.getHeading();

  // Camera
  camera.update();

  // Lidars
  lidars.update();

  // Orbit
  orbit.setRole(role);
  orbit.setGoalData(camera.getAttackGoal(), camera.getDefendGoal());
  orbit.setBallData(camera.getBall());
  orbit.setCompAngle(heading);
  orbit.setCoords(lidars.getCoords());

  // More Orbit
  orbit.calculateMoveData();
  orbit.calculateRotation();

  // Movement
  move = orbit.getMoveData();
  if(move.brake){
    motors.brake();
  }else{
    motors.moveDirection(move);
  }
}
