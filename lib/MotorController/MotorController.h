#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Motor.h>
#include <Common.h>
#include <Defines.h>
#include <Pins.h>

class MotorController {
  public:
    MotorController();

    void motorSetup();

    void moveDirection(int angle, int speed, int rotation);
    void rotate(int rotation);
    void move(int FR, int BR, int BL, int FL);
    void brake();

  private:
    Motor motorFR, motorBR, motorBL, motorFL;
};
#endif
