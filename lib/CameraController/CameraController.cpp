#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::setAttackGoal(Image aGoal){
  attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
  //attackGoal.distance = calculateGoalDistance(aGoal.pixels);
}

void CameraController::setDefendGoal(Image dGoal){
  defendGoal.angle = calculateAngle(aGoal.x, aGoal.y);
  //defendGoal.distance = calculateGoalDistance(dGoal.pixels);
}

void CameraController::setBall(Image ballImage){
  ball.angle = calculateAngle(ballImage.x,ballImage.y);
  //ball.distance = calculateDistance(ballImage.pixels);
}

int CameraController::calculateAngle(int x, int y){

}

int CameraController::calculateGoalDistance(int pixels){

}

int CameraController::calculateBallDistance(int pixels){

}

EntityData CameraController::getAttackGoal(){

}

EntityData CameraController::getDefendGoal(){

}

EntityData CameraController::getBall(){

}
