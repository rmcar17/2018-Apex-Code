#include "Camera.h"

Camera::Camera(){

}

void Camera::setup(){
  CAMERA_SERIAL.begin(9600);
}

void Camera::update(){

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
