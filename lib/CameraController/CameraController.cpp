#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::setAttackGoal(Image aGoal){
  attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
  //attackGoal.distance = calculateGoalDistance(aGoal.pixels);
}

void CameraController::setDefendGoal(Image dGoal){
  defendGoal.angle = calculateAngle(dGoal.x, dGoal.y);
  //defendGoal.distance = calculateGoalDistance(dGoal.pixels);
}

void CameraController::setBall(Image ballImage){
  ball.angle = calculateAngle(ballImage.x,ballImage.y);
  //ball.distance = calculateDistance(ballImage.pixels);
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(450 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

int CameraController::calculateGoalDistance(int pixels){
  return 0;
}

int CameraController::calculateBallDistance(int pixels){
  return 0;
}

EntityData CameraController::getAttackGoal(){
  return {0,0,0};
}

EntityData CameraController::getDefendGoal(){
  return {0,0,0};
}

EntityData CameraController::getBall(){
  return {0,0,0};
}
