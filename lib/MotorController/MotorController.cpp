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
  int angle = movement.angle;
  int speed = movement.speed;
  int rotation = movement.rotation;

  double frontRightSpeed;
  double backRightSpeed;
  double backLeftSpeed;
  double frontLeftSpeed;

  if(angle == -1)
  {
    frontRightSpeed = rotation;
    backRightSpeed = -rotation;
    backLeftSpeed = -rotation;
    frontLeftSpeed = rotation;
  }
  else
  {
    double multiplier;

    double newAngle = toRadians(mod(320 + angle, 360));

    double b = 1 / (cos(PI / 18) * tan(newAngle));
    double a = 1 - b * sin(PI / 18);
    if(newAngle > 0 && newAngle < PI){
      b *= -1;
      a *= -1;
    }

    multiplier = 255 / max(abs(a), abs(b));
    a *= multiplier;
    b *= multiplier;

    frontRightSpeed = -a + rotation;
    backRightSpeed = b - rotation;
    backLeftSpeed = a - rotation;
    frontLeftSpeed = -b + rotation;

    multiplier = speed / max(abs(frontRightSpeed), max(abs(backRightSpeed), max(abs(backLeftSpeed), abs(frontLeftSpeed))));

    frontRightSpeed = round(frontRightSpeed * multiplier);
    backRightSpeed = round(backRightSpeed * multiplier);
    backLeftSpeed = round(backLeftSpeed * multiplier);
    frontLeftSpeed = round(frontLeftSpeed * multiplier);
  }

  move(frontRightSpeed, backRightSpeed, backLeftSpeed, frontLeftSpeed);

  // motorFR.move(constrain(frontRightSpeed, -255, 255));
  // motorBR.move(constrain(backRightSpeed, -255, 255));
  // motorBL.move(constrain(backLeftSpeed, -255, 255));
  // motorFL.move(constrain(frontLeftSpeed, -255, 255));
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
  motorFR.move(0);
  motorBR.move(0);
  motorBL.move(0);
  motorFL.move(0);
}
