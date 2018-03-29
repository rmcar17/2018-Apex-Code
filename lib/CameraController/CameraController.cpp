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
  double cameraDistance = sqrt(x*x+y*y);

  return cameraDistance < CAM_SWITCH_D ? calculateCircleDistance(cameraDistance) : calculateConeDistance(cameraDistance);
}

double CameraController::calculateCircleDistance(double distance){
  double mirrorHeight = CAMERA_ORIGIN-sqrt(pow(CIRCLE_RADIUS,2)-pow(distance,2));

  double tangentAngle = atan(distance / sqrt(pow(CIRCLE_RADIUS,2) + pow(distance,2)));
  double reflectionAngle = atan(mirrorHeight-CAMERA_HEIGHT) / distance;

  double finalDistance = distance + mirrorHeight * tan(90 - reflectionAngle + 2 * tangentAngle);
  return finalDistance;
}

double CameraController::calculateConeDistance(double distance){
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
