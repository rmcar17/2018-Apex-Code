#include "Camera.h"

Camera::Camera(){

}

void Camera::setup(){
  cameraSerial.begin(9600);
}

void Camera::update(){
  Serial.println(cameraSerial.read());
}

Image Camera::getAttackGoal(){
  return attackGoal;
}

Image Camera::getDefendGoal(){
  return defendGoal;
}

Image Camera::getBall(){
  return ball;
}
