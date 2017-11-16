#include <Arduino.h>

#include <Debug.h>
#include <Defines.h>
#include <Pins.h>

#include <MotorController.h>
#include <Motor.h>

Motor motor1;

void setup() {
  motor1 = Motor(MOTOR1_PWM,MOTOR1_IN1,MOTOR1_IN2);
    // put your setup code here, to run once:
}

void loop() {
  motor1.move(255);
    // put your main code here, to run repeatedly:
}
