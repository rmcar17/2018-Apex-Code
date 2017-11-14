#include "MotorController.h"

MotorController::MotorController(){

}

void MotorController::MoveDirection(int angle, int speed, int rotation){
  double multiplier;

  double newAngle = toRadians(mod(45-angle,360));

  int b = angle > 135 && angle < 315 ? -speed : speed;
  int a = round(b * tan(newAngle));

  if(abs(a)>speed){
    multiplier = abs(speed/a);
    b = round(b*multiplier);
    a = round(a*multiplier);
  }

  int frontRightSpeed = a + rotation;
  int backRightSpeed = -b + rotation;
  int backLeftSpeed = -a + rotation;
  int frontLeftSpeed = b + rotation;



  multiplier = speed/max(abs(frontRightSpeed),max(abs(backRightSpeed),max(abs(backLeftSpeed),abs(frontLeftSpeed))));

  frontRightSpeed = round(frontRightSpeed*multiplier);
  backRightSpeed = round(backRightSpeed*multiplier);
  backLeftSpeed = round(backLeftSpeed*multiplier);
  frontLeftSpeed = round(frontLeftSpeed*multiplier);

  /*
  Move Motors their various speeds
  */
}
