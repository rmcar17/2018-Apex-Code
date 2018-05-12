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
  calculateEntity(&ball, camera.getBall());
  calculateEntity(&attackGoal, camera.getAttackGoal());
  calculateEntity(&defendGoal, camera.getDefendGoal());

  #if DEBUG_CAMERA
    Serial.print("BALL: ");
    Serial.print(ball.arg);
    Serial.print(" ");
    Serial.println(ball.mag);
  #endif
}

void CameraController::calculateEntity(Vector *entity, Image image){
  *entity = image.visible ? Vector(calculateDistance(image.x, image.y), calculateAngle(image.x, image.y)) : Vector(0,0);
}

int CameraController::calculateAngle(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  int angle = mod(630 - round(toDegrees(atan2(Y,X))),360);
  return angle;
}

double CameraController::calculateDistance(int x, int y){
  double X = CAM_CENTRE_X-x;
  double Y = CAM_CENTRE_Y-y;

  double cameraDistance = sqrt(X*X+Y*Y) * PIXEL_TO_MM;
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
