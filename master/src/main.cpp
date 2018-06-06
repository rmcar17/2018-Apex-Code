#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Orbit.h>
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
#include <t3spi.h>

Compass comp;

CameraController camera;

MotorController motors;

LightSensorController lights;
Orbit orbit;

Role role;

MoveData move;

T3SPI spi;

int lightVector, lightLine;
volatile uint16_t dataOut[1], dataIn[1];

uint16_t transaction(uint8_t command, uint16_t data = 0){
  dataOut[0] = (command << 10) | (data & 0x3FF);

  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT); 
  spi.txrx16(dataOut, dataIn, 1, CTAR_0, MASTER_CS_LIGHT); 

  return dataIn[0];
}


void setup() {
  #if DEBUG_ANY
    Serial.begin(38400);
  #endif

  lights.setup();

  motors.motorSetup();

  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  // SPI
  spi = T3SPI();
  spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_LIGHT, CS_ActiveLOW);
  spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
  spi.enableCS(CS0, CS_ActiveLOW);
}

void loop() {
  comp.updateGyro();
  int heading = comp.getHeading();
  lightVector = (int)transaction(((uint8_t)0));
  if(lightVector==65535.00){
    lightVector = -1;
  }
  lights.setComp(heading);
  lights.setVector(lightVector);
  // Serial.print(lights.getVectorAngle());
  // Serial.print("\t");
  // Serial.print(lights.prevAngle);
  // Serial.print("\t");
  // Serial.print(lights.getLineAngle());
  // Serial.print("\t");
  // Serial.print(lights.danger);
  // Serial.print("\t");
  // Serial.print(lights.a);
  // Serial.print("\t");
  // Serial.println(lights.b);

  lights.updateWithComp();
  if(lights.getLineAngle()!=-1){
    motors.moveDirection({lights.getLineAngle()+180-heading,100,0});
  }else{
    motors.brake();
  }

}

