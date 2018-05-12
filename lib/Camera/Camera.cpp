#include "Camera.h"

Camera::Camera(){

}

void Camera::setup(){
  cameraSerial.begin(9600);
  update();
  blueAttack = isBlueAttack();
}

void Camera::update(){
  if(!cameraTimer.hasTimePassed()){
    return;
  }
  while(cameraSerial.read() != 1);
  for(int i = 0; i < CAM_BUFFER_NUM; i++){
    while(!(cameraSerial.available() > 0));
    camBuffer[i] = cameraSerial.read();
  }
  ball.x = camBuffer[0] + camBuffer[1];
  ball.y = camBuffer[2];
  ball.visible = !(ball.x == 0 && ball.y == 0);

  blueGoal.x = camBuffer[3] + camBuffer[4];
  blueGoal.y = camBuffer[5];
  blueGoal.visible = !(blueGoal.x == 0 && blueGoal.y == 0);

  yellowGoal.x = camBuffer[6] + camBuffer[7];
  yellowGoal.y = camBuffer[8];
  yellowGoal.visible = !(yellowGoal.x == 0 && yellowGoal.y == 0);

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
    Serial.println(")");
  #endif

  if(blueAttack == Role::undecided){
    blueAttack = isBlueAttack();
  }
}

Image Camera::getBall(){
  return ball;
}

Image Camera::getAttackGoal(){
  return blueAttack == Role::attack ? blueGoal : yellowGoal;
}

Image Camera::getDefendGoal(){
  return blueAttack == Role::attack ? yellowGoal : blueGoal;
}

Role Camera::isBlueAttack(){
  #if ATTACK_GOAL_OVERIDE
    return OVERIDE_BLUE ? Role::attack : Role::defend;
  #else
    if((blueGoal.visible && blueGoal.y < CAM_CENTRE_Y) || (yellowGoal.visible && yellowGoal.y > CAM_CENTRE_Y)){
      return Role::attack;
    }
    else if ((blueGoal.visible && blueGoal.y > CAM_CENTRE_Y) || (yellowGoal.visible && yellowGoal.y < CAM_CENTRE_Y)){
      return Role::defend;
    }
    return Role::undecided;
  #endif
}
