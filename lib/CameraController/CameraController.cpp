#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::setup(){
  camera.setup();
}

void CameraController::update(){
  if(camera.isAvailable()){
    camera.update();
    calculateEntities();
    cameraTimer.update();
  }
}

void CameraController::calculateEntities(){
  calculateBall(camera.getBall());
  calculateGoal(&attackGoal, camera.getAttackGoal());
  // Serial.println(attackGoal.arg);
  calculateGoal(&defendGoal, camera.getDefendGoal());

  #if DEBUG_CAMERA
    Serial.print("BALL: ");
    Serial.print(ball.arg);
    Serial.print(" ");
    Serial.println(ball.mag);
  #endif
}

void CameraController::calculateBall(Image ballImage){
  ball = ballImage.visible ? Vector(calculateBallDistance(getDistance(ballImage)), calculateAngle(ballImage.x, ballImage.y)) : Vector(0,0);
}

void CameraController::calculateGoal(Vector *goal, Image goalImage){
  *goal = goalImage.visible ? Vector(calculateBallDistance(getDistance(goalImage)), calculateAngle(goalImage.x, goalImage.y)) : Vector(0,0);
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(630 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

double CameraController::getDistance(Image image){
  int x = image.x - CAM_CENTRE_X;
  int y = image.y - CAM_CENTRE_Y;
  return sqrt(x * x + y * y);
}

double CameraController::calculateBallDistance(double distance){
  return 0.8872 * exp(0.0618 * distance) + 100;
}

Vector CameraController::getAttackGoal(){
  return attackGoal;
}

Vector CameraController::getDefendGoal(){
  return defendGoal;
}

Vector CameraController::getBall(){
  return ball;
}
