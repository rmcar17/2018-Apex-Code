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

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;
LightGate gate;

Orbit orbit;

Role role;

// RoleController RC;

MoveData move;

T3SPI spi;

Vector vector = Vector(0,0);

bool inCorner;

int lightVector;
volatile uint16_t dataOut[1], dataIn[1];

uint16_t transaction(uint8_t command, uint16_t data = 0){
  dataOut[0] = (command << 14) | (data & 0x3FFF);

  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT);

  return dataIn[0];
}

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

  gate.setup();

  orbit.setup();
  orbit.resetAllData();


  // SPI
  spi = T3SPI();
  spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_LIGHT, CS_ActiveLOW);
  spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
  spi.enableCS(CS0, CS_ActiveLOW);

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

  // More Orbit
  orbit.calculateMoveData();
  orbit.calculateRotation();

  // Movement
  move = orbit.getMoveData();
  motors.moveDirection(move);

  float horD = (lidars.lidarLeft + lidars.lidarRight) / 2;
  float verD = lidars.lidarBack;
  inCorner = true;
  if(horD < 500){
    inCorner  = false;
  }

  if(inCorner){
    if(verD>500){
      Serial.println("We\'re stuck at front!");
    } else{
      Serial.println("We\'re stuck at back!");
    }
  } else{
    Serial.println("we\'re not stuck!");
  }

  // End Loop
  orbit.resetAllData();
}
