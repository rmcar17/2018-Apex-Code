#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Camera.h>
#include <CameraController.h>
#include <Kicker.h>
#include <LightGate.h>
#include <RoleController.h>
#include <Orbit.h>
#include <Bluetooth.h>
#include <Timer.h>
#include <PID.h>
#include <Common.h>
#include <Vector.h>
#include <Role.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>
#include <t3spi.h>
#include <Lidar.h>

LIDAR lidars;

Bluetooth bt;

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;

LightGate lg;

Orbit orbit;

Role role;

// RoleController RC;

MoveData move;

T3SPI spi;

Vector vector = Vector(0,0);

bool inCorner;

int lightVector;

bool hasSurged = true;
Timer surgeTimer = Timer(500);

void setup() {
  pinMode(TEENSY_LED, OUTPUT);

  pinMode(17, INPUT);

  #if DEBUG_ANY
    Serial.begin(38400);
  #endif

  motors.motorSetup();
  motors.brake();

  camera.setup();

  digitalWrite(TEENSY_LED, HIGH);

  bt.setup();

  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  orbit.setup();
  orbit.resetAllData();

  lidars.setup();

  lg.setup();

  role = Role::attack; /* PLEASE CHECK BATTERY VOLTAGE */

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

  //Bluetooth
  bt.receive();

  //MUST DECIDE ROLES HERE

  Vector ball = camera.getBall();
  Vector robotPosition = lidars.getCoords();
  Vector ballPosition = robotPosition + ball;

  int btSendData[BT_DATA_SIZE] = {round(ballPosition.i), round(ballPosition.j), round(robotPosition.i), round(robotPosition.j), role};
  bt.send(&btSendData[0]);

  // Orbit
  orbit.setRole(role);
  orbit.setGoalData(camera.getAttackGoal(), camera.getDefendGoal());
  orbit.setBallData(camera.getBall());
  // orbit.setLightGate(lg.hasBall());
  orbit.setCompAngle(heading);
  orbit.setCoords(lidars.getCoords());
  orbit.setBTData(bt.getOtherBallPos());

  // More Orbit
  orbit.calculateMoveData();
  orbit.calculateRotation();

  orbit.manageKicker();

  // Movement
  move = orbit.getMoveData();
  if(role == Role::attack && (!hasSurged || !surgeTimer.hasTimePassedNoUpdate()) && analogRead(17) > 0){
    if(!hasSurged){
      surgeTimer.update();
      hasSurged = true;
    }
    motors.moveDirection({0,MAX_SPEED,move.rotation});
  }
  else{
    if(move.brake){
      motors.brake();
    }else{
      motors.moveDirection(move);
    }
  }

  orbit.resetAllData();
  // End Loop
}
