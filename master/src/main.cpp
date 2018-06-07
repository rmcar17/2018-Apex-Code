#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <Compass.h>
#include <LightSensor.h>
#include <LightSensorController.h>
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
#include <Lidar.h>
#include <Bluetooth>

LIDAR lidar = LIDAR();

Bluetooth bt;

void setup() {
  Serial.begin(38400);
  lidar.init();
  bt.init();
}

void loop() {
  double btCMD = bt.receive();
  lidar.read();
  for(int i; i < 4; i++){
    Serial.println(lidar.lidarVal[i]);
    Serial.print("\t");
  }
  Serial.println();
  // comp.updateGyro();
  // int heading = comp.getHeading();
  // lightVector = (int)transaction(((uint8_t)0));
  // if(lightVector==65535.00){
  //   lightVector = -1;
  // }
  // lights.setComp(heading);
  // lights.setVector(lightVector);

  // lights.updateWithComp();
  // if(lights.getLineAngle()!=-1){
  //   motors.moveDirection({lights.getLineAngle()+180-heading,100,0});
  // }else{
  //   motors.brake();
  // }
}

