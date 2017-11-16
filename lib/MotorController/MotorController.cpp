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

void MotorController::moveDirection(int angle, int speed, int rotation){
  double multiplier;

  double newAngle = toRadians(mod(45-angle,360));

  double b = angle > 135 && angle < 315 ? -speed : speed;
  double a = round(b * tan(newAngle));

  Serial.println(speed/a,8);

  if(abs(a)>speed){
    multiplier = abs(speed/a);
    b = b*multiplier;
    a = a*multiplier;
  }
  int frontRightSpeed = ((int) a) + rotation;
  int backRightSpeed = -((int) b) + rotation;
  int backLeftSpeed = -((int) a) + rotation;
  int frontLeftSpeed = ((int) b) + rotation;



  multiplier = speed/max(abs(frontRightSpeed),max(abs(backRightSpeed),max(abs(backLeftSpeed),abs(frontLeftSpeed))));

  frontRightSpeed = round(frontRightSpeed*multiplier);
  backRightSpeed = round(backRightSpeed*multiplier);
  backLeftSpeed = round(backLeftSpeed*multiplier);
  frontLeftSpeed = round(frontLeftSpeed*multiplier);

  motorFR.move(frontRightSpeed);
  motorBR.move(backRightSpeed);
  motorBL.move(backLeftSpeed);
  motorFL.move(frontLeftSpeed);
}
