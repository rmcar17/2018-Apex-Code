#include "MotorController.h"

MotorController::MotorController(){

}

void MotorController::motorSetup(){
  motorFR = Motor(MOTORFR_PWM,MOTORFR_DIR,MOTORFR_BRK,MOTORFR_REV);
  motorBR = Motor(MOTORBR_PWM,MOTORBR_DIR,MOTORBR_BRK,MOTORBR_REV);
  motorBL = Motor(MOTORBL_PWM,MOTORBL_DIR,MOTORBL_BRK,MOTORBL_REV);
  motorFL = Motor(MOTORFL_PWM,MOTORFL_DIR,MOTORFL_BRK,MOTORFL_REV);
  motorFR.motorSetup();
  motorBR.motorSetup();
  motorBL.motorSetup();
  motorFL.motorSetup();
}

void MotorController::moveDirection(MoveData movement){
  int angle = movement.angle + MOVEMENT_ANGLE_OFFSET;
  int speed = movement.speed;
  int rotation = movement.rotation + MOVEMENT_ROTATION_OFFSET;

  double frontRightSpeed;
  double backRightSpeed;
  double backLeftSpeed;
  double frontLeftSpeed;

  if(angle == -1)
  {
    frontRightSpeed = -rotation;
    backRightSpeed = -rotation;
    backLeftSpeed = -rotation;
    frontLeftSpeed = -rotation;
  }
  else
  {
    double multiplier;

    double newAngle = toRadians(mod(320 + angle, 360));

    double b = 1 / (cos(PI / 18) * tan(newAngle != 0 ? newAngle : 0.001));
    double a = 1 - b * sin(PI / 18);
    if(newAngle >= 0 && newAngle < PI){
      b *= -1;
      a *= -1;
    }

    multiplier = speed / max(abs(a), abs(b));
    a *= multiplier;
    b *= multiplier;

    frontRightSpeed = -a-rotation;
    backRightSpeed = b-rotation;
    backLeftSpeed = a-rotation;
    frontLeftSpeed = -b-rotation;

    if(max(abs(frontRightSpeed), max(abs(backRightSpeed), max(abs(backLeftSpeed), abs(frontLeftSpeed)))) > MAX_SPEED){
      multiplier = MAX_SPEED / max(abs(frontRightSpeed), max(abs(backRightSpeed), max(abs(backLeftSpeed), abs(frontLeftSpeed))));

      frontRightSpeed = frontRightSpeed * multiplier;
      backRightSpeed = backRightSpeed * multiplier;
      backLeftSpeed = backLeftSpeed * multiplier;
      frontLeftSpeed = frontLeftSpeed * multiplier;
    }
  }

  move(round(frontRightSpeed), round(backRightSpeed), round(backLeftSpeed), round(frontLeftSpeed));
}

void MotorController::rotate(int rotation){
  move(rotation, rotation, rotation, rotation);
}

void MotorController::move(int FR, int BR, int BL, int FL){
  motorFR.move(constrain(FR, -255, 255));
  motorBR.move(constrain(BR, -255, 255));
  motorBL.move(constrain(BL, -255, 255));
  motorFL.move(constrain(FL, -255, 255));
}

void MotorController::brake(){
  motorFR.brake();
  motorBR.brake();
  motorBL.brake();
  motorFL.brake();
}