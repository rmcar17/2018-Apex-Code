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
  attackGoal.distance = calculateGoalDistance(aGoal.pixels);
  attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
}

void CameraController::calculateDefendGoal(Image dGoal){
  defendGoal.distance = calculateGoalDistance(dGoal.pixels);
  defendGoal.angle = calculateAngle(dGoal.x, dGoal.y);
}

void CameraController::calculateBall(Image ballImage){
  ball.distance = calculateBallDistance(ballImage.pixels);
  ball.angle = calculateAngle(ballImage.x,ballImage.y);
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
  return ((double) pixels) / BALL_PIXELS;
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
