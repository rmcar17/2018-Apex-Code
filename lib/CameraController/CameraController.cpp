#include "CameraController.h"

CameraController::CameraController(){

}

void CameraController::setup(){
  camera.setup();
}

void CameraController::update(){
  camera.update();
}

void CameraController::calculateEntities(){
  calculateGoals(camera.getAttackGoal(), camera.getDefendGoal());
  calculateBall(camera.getBall());
}

void CameraController::calculateGoals(Image aGoal, Image dGoal){
  if(aGoal.visible){
    attackGoal.angle = calculateAngle(aGoal.x, aGoal.y);
    attackGoal.distance = calculateDistance(aGoal.x, aGoal.y);
  }
  else{
    attackGoal.angle = -1;
    attackGoal.distance = -1;
  }
  if(dGoal.visible){
    defendGoal.angle = calculateAngle(dGoal.x, dGoal.y);
    defendGoal.distance = calculateDistance(dGoal.x, dGoal.y);
  }
  else{
    defendGoal.angle = -1;
    defendGoal.distance = -1;
  }
}

void CameraController::calculateBall(Image ballImage){
  if(ballImage.visible){
    ball.angle = calculateAngle(ballImage.x, ballImage.y);
    ball.distance = calculateDistance(ballImage.x, ballImage.y);
  }
  else{
    ball.angle = -1;
    ball.distance = -1;
  }
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(450 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

double CameraController::calculateDistance(int x, int y){
  double cameraDistance = sqrt(x*x+y*y);

  return cameraDistance < CAM_SWITCH_D ? calculateCircleDistance(cameraDistance) : calculateConeDistance(cameraDistance);
}

double CameraController::calculateCircleDistance(double distance){
  double mirrorHeight = CAMERA_ORIGIN-sqrt(pow(CIRCLE_RADIUS,2)-pow(distance,2));

  double tangentAngle = atan(distance / sqrt(pow(CIRCLE_RADIUS,2) - pow(distance,2)));
  double reflectionAngle = atan((mirrorHeight-CAMERA_HEIGHT) / distance);

  double finalDistance = distance + mirrorHeight * abs(tan(PI/2 - reflectionAngle + 2 * tangentAngle));
  return finalDistance;
}

double CameraController::calculateConeDistance(double distance){
  double mirrorHeight = (sqrt(3) / 3) * distance + CAMERA_ORIGIN - sqrt(pow(32,2)+pow(CAM_SWITCH_D,2)) - (sqrt(3) / 3) * CAM_SWITCH_D;

  double reflectionAngle = atan((mirrorHeight-CAMERA_HEIGHT) / distance);

  double finalDistance = distance + mirrorHeight * tan(5*PI/6 - reflectionAngle);
  return finalDistance;
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
