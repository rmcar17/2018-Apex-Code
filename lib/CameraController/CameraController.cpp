#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::setAttackGoal(int x, int y, int pixels){
  //Image aGoal = Camera.getAttackGoal();
  //attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
}

void CameraController::setDefendGoal(int x, int y, int pixels){
  //Image dGoal = Camera.getAttackGoal();
}

void CameraController::setBall(int x, int y, int pixels){
  //Image ballImage = Camera.getBall();
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
