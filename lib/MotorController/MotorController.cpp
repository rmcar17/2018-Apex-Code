#include "MotorController.h"

MotorController::MotorController(){

}

void MotorController::motorSetup(){
  motorFR = Motor(MOTORFR_PWM,MOTORFR_IN1,MOTORFR_IN2);
  motorBR = Motor(MOTORBR_PWM,MOTORBR_IN1,MOTORBR_IN2);
  motorBL = Motor(MOTORBL_PWM,MOTORBL_IN1,MOTORBL_IN2);
  motorFL = Motor(MOTORFL_PWM,MOTORFL_IN1,MOTORFL_IN2);
  motorFR.motorSetup();
  motorBR.motorSetup();
  motorBL.motorSetup();
  motorFL.motorSetup();
}

void MotorController::moveDirection(MoveData movement){
  int angle = movement.angle;
  int speed = movement.speed;
  int rotation = movement.rotation;
  Serial.println(speed);
  double frontRightSpeed;
  double backRightSpeed;
  double backLeftSpeed;
  double frontLeftSpeed;

  if(angle == -1)
  {
    frontRightSpeed = rotation;
    backRightSpeed = rotation;
    backLeftSpeed = rotation;
    frontLeftSpeed = rotation;
  }
  else
  {
    double multiplier;

    double newAngle = toRadians(mod(45-angle, 360));

    double b = angle > 135 && angle <= 315 ? -speed : speed;
    double a = round(b * tan(newAngle));

    if(abs(a) > speed)
    {
      multiplier = abs(speed / a);
      b = b * multiplier;
      a = a * multiplier;
    }

    frontRightSpeed = -a + rotation;
    backRightSpeed = -b + rotation;
    backLeftSpeed = a + rotation;
    frontLeftSpeed = b + rotation;

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
