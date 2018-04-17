#include "Camera.h"

Camera::Camera(){

}

void Camera::setup(){
  cameraSerial.begin(9600);
  update();
  blueAttack = isBlueAttack();
}

void Camera::update(){
  while(cameraSerial.read() != 1);
  for(int i = 0; i < CAM_BUFFER_NUM; i++){
    while(!cameraSerial.available());
    camBuffer[i] = cameraSerial.read();
  }
  ball.x = camBuffer[0] + camBuffer[1];
  ball.y = camBuffer[2];

  blueGoal.x = camBuffer[3] + camBuffer[4];
  blueGoal.y = camBuffer[5];

  yellowGoal.x = camBuffer[6] + camBuffer[7];
  yellowGoal.y = camBuffer[8];

  #if DEBUG_CAMERA_RAW
    Serial.print("Ball (");
    Serial.print(ball.x);
    Serial.print(", ");
    Serial.print(ball.y);
    Serial.print(") Blue Goal (");
    Serial.print(blueGoal.x);
    Serial.print(", ");
    Serial.print(blueGoal.y);
    Serial.print(") Yellow Goal (");
    Serial.print(yellowGoal.x);
    Serial.print(", ");
    Serial.print(yellowGoal.y);
    Serial.println(")")
  #endif

  if(blueAttack == PlayMode::undecided){
    blueAttack = isBlueAttack();
  }
}

Image Camera::getBall(){
  return ball;
}

Image Camera::getAttackGoal(){
  return blueAttack == PlayMode::attack ? blueGoal : yellowGoal;
}

Image Camera::getDefendGoal(){
  return blueAttack == PlayMode::attack ? yellowGoal : blueGoal;
}

PlayMode Camera::isBlueAttack(){
  #if ATTACK_GOAL_OVERIDE
    return OVERIDE_BLUE ? PlayMode::attack : PlayMode::defend;
  #else
    if((blueGoal.visible && blueGoal.y < CAM_CENTRE_Y) || (yellowGoal.visible && yellowGoal.y > CAM_CENTRE_Y)){
      return PlayMode::attack;
    }
    else if ((blueGoal.visible && blueGoal.y > CAM_CENTRE_Y) || (yellowGoal.visible && yellowGoal.y < CAM_CENTRE_Y)){
      return PlayMode::defend;
    }
    return PlayMode::undecided;
  #endif
}
