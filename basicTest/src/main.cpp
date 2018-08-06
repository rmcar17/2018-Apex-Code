#include <Arduino.h>
#include <MotorController.h>
#include <Motor.h>
#include <Compass.h>
#include <Camera.h>
#include <CameraController.h>
#include <Common.h>
#include <Vector.h>
#include <MoveData.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>
#include <Lidar.h>

LIDAR lidars;

Compass comp;

CameraController camera;

MotorController motors;

MoveData move;

Vector vector = Vector(0,0);

void setup() {
  pinMode(TEENSY_LED, OUTPUT);
  Serial.begin(38400);
  Serial.println("Setting up camera...");
  camera.setup();
  digitalWrite(TEENSY_LED, HIGH);
  Serial.println("Done");


  Wire.begin();
  comp.compassSetup();
  comp.calibrate();

  motors.motorSetup();
  motors.brake();

  lidars.setup();

  digitalWrite(TEENSY_LED, LOW);
}

void loop() {
  //Compass
  comp.updateGyro();
  int heading = comp.getHeading();

  // Camera
  camera.update();
  Vector ball = camera.getBall();

  // LIDAR
  lidars.setComp(heading);
  lidars.update();

  // Motors
  motors.moveDirection({0,100,0});

  // Print
  Serial.print(heading);
  Serial.print("\t");
  Serial.print(ball.arg);
  Serial.print("\t");
  Serial.print(ball.mag);
  Serial.print("\t");
  Serial.print(lidars.lidarValues[0]);
  Serial.print("\t");
  Serial.print(lidars.lidarValues[1]);
  Serial.print("\t");
  Serial.print(lidars.lidarValues[2]);
  Serial.print("\t");
  Serial.println(lidars.lidarValues[3]);
}
