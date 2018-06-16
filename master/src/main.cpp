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
#include <Bluetooth.h>

SoftwareSerial blueSerial(7,8);

LIDAR lidars = LIDAR();

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;
LightGate gate;

Orbit orbit;

Role role;

MoveData move;

Bluetooth bt;

T3SPI spi;

int lightVector;
volatile uint16_t dataOut[1], dataIn[1];

uint16_t transaction(uint8_t command, uint16_t data = 0){
  dataOut[0] = (command << 10) | (data & 0x3FF);

  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT);
  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT);

  return dataIn[0];
}

unsigned long int timeVar;

void setup() {
  pinMode(TEENSY_LED, OUTPUT);
  #if DEBUG_ANY
    Serial.begin(38400);
  #endif
  camera.setup();

  digitalWrite(TEENSY_LED, HIGH);


  motors.motorSetup();
  motors.brake();

  gate.setup();

  orbit.setup();
  orbit.resetAllData();

  // SPI
  // spi = T3SPI();
  // spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_LIGHT, CS_ActiveLOW);
  // spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
  // spi.enableCS(CS0, CS_ActiveLOW);

  bt.init();

  role = Role::defend;

  lidars.setup();
  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  timeVar = micros();

  digitalWrite(TEENSY_LED, LOW);
}

void loop() {
  // Compass
  timeVar = micros();
  comp.updateGyro();
  Serial.println(micros()-timeVar);
  int heading = comp.getHeading();

  // LIDAR
  lidars.setComp(comp.getHeading());
  lidars.update();
  // Camera
  camera.update();

  // Light
  // lightVector = (int)transaction(((uint8_t)0));
  // if(lightVector==65535){
  //   lightVector = -1;
  // }

  // lights.setComp(heading);
  // lights.setVector(lightVector);
  // lights.updateWithComp();

  // // Orbit
  orbit.setRole(role);
  orbit.setGoalData(camera.getAttackGoal(), camera.getDefendGoal());
  orbit.setBallData(camera.getBall());
  orbit.setCompAngle(heading);
  orbit.setLightGate(gate.hasBall());
  orbit.setCoords(lidars.getCoords());
  orbit.calculateMoveData();
  orbit.calculateRotation();
  // orbit.setLightValue(lights.getLineAngle(),lights.danger);
  // orbit.calculateLine();

  // Bluetooth
  double btCMD = bt.receive();

  // Movement
  move = orbit.getMoveData();
  // Serial.println(move.angle);
  // move.angle = -1;
  motors.moveDirection(move);
  // motors.moveDirection({0,100,0});

  // End Loop
  orbit.resetAllData();
}
