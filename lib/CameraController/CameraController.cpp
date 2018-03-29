#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::updateCamera(){
  // camera.update()
}

void CameraController::calculateEntities(){
  // calculateAttackGoal(camera.getAttackGoal());
  // calculateDefendGoal(camera.getDefendGoal());
  // calculateBall(camera.getBall());
}

void CameraController::calculateAttackGoal(Image aGoal){
  if(aGoal.visible){
    attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
  }
  attackGoal.visible = aGoal.visible;
}

void CameraController::calculateDefendGoal(Image dGoal){
  if(dGoal.visible){
    defendGoal.angle = calculateAngle(dGoal.x, dGoal.y);
  }
  defendGoal.visible = dGoal.visible;
}

void CameraController::calculateBall(Image ballImage){
  if(ballImage.visible){
    ball.angle = calculateAngle(ballImage.x,ballImage.y);
  }
  ball.visible = ballImage.visible;
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(450 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

double CameraController::calculateDistance(int x, int y){
  return 0;
}

EntityData CameraController::getAttackGoal(){
  return attackGoal;
}

EntityData CameraController::getDefendGoal(){
  return defendGoal;
}

EntityData CameraController::getBall(){
  return ball;
}
