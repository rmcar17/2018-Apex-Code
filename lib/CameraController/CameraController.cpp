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
  attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
  attackGoal.distance = calculateGoalDistance(aGoal.pixels);
}

void CameraController::calculateDefendGoal(Image dGoal){
  defendGoal.angle = calculateAngle(dGoal.x, dGoal.y);
  defendGoal.distance = calculateGoalDistance(dGoal.pixels);
}

void CameraController::calculateBall(Image ballImage){
  ball.angle = calculateAngle(ballImage.x,ballImage.y);
  ball.distance = calculateBallDistance(ballImage.pixels);
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(450 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

double CameraController::calculateGoalDistance(int pixels){
  return ((double) pixels) / GOAL_PIXELS;
}

double CameraController::calculateBallDistance(int pixels){
  return ((double) pixels) / GOAL_PIXELS;
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
