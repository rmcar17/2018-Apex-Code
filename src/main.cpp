#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <TSOPController.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Orbit.h>
#include <PID.h>
#include <Common.h>
#include <PlayMode.h>
#include <EntityData.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <t3spi.h>
#include <Pins.h>

int ballVector, ballLine;
volatile uint16_t dataOut[1], dataIn[1];

uint16_t transaction(uint8_t command, uint16_t data = 0){
  dataOut[0] = (command << 10) | (data & 0x3FF);

  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT); 
  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT); 

  return dataIn[0];
}

Compass comp;
TSOPController tsops;

MotorController motors;

LightSensorController lights;
Orbit orbit;

PlayMode role;
T3SPI spi;

EntityData ball;
EntityData goal;
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

  lights.setup();

  tsops.TSOPSetup();

  orbit.resetAllData();

  // SPI
  spi = T3SPI();
  spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_LIGHT, CS_ActiveLOW);
  spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV32);
  spi.enableCS(CS0, CS_ActiveLOW);
  
  role = PlayMode::attacker;

  goal.angle = -1;
  goal.distance = 0;
  goal.visible = false;
}

void loop() {
  comp.updateGyro();
  lights.update();
  
  ball = tsops.getBallData();
  ballVector = transaction(0);
  ballLine = transaction(1);

  //Create another class which fetches
  //goal data which takes an input of
  //the robot's current role

  //Create another class which checks
  //whether the robots should switch
  //roles

  orbit.setRole(role);
  orbit.setGoalData(goal);
  orbit.setBallData(ball);
  orbit.setCompAngle(comp.getHeading());

  orbit.calculateMoveData();
  orbit.calculateRotation();

  move = orbit.getMoveData();

  motors.moveDirection(move);

  orbit.resetAllData();

  lights.update();

  Serial.print(ballVector);
  Serial.print("\t");
  Serial.println(ballLine);
}
