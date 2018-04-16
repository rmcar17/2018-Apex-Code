#include "Camera.h"

Camera::Camera(){

}

void Camera::setup(){
  cameraSerial.begin(9600);
}

void Camera::update(){
  while(cameraSerial.read() != 1);
  for(int i = 0; i < CAM_BUFFER_NUM; i++){
    while(!cameraSerial.available());
    camBuffer[i] = cameraSerial.read();
    Serial.println(camBuffer[i]);
  }
  ball.x = camBuffer[0] + camBuffer[1];
  ball.y = camBuffer[2];

  blueGoal.x = camBuffer[3] + camBuffer[4];
  blueGoal.y = camBuffer[5];

  yellowGoal.x = camBuffer[6] + camBuffer[7];
  yellowGoal.y = camBuffer[8];
}

Image Camera::getBall(){
  return ball;
}

Image Camera::getAttackGoal(){
  return attackGoal;
}

Image Camera::getDefendGoal(){
  return defendGoal;
}
