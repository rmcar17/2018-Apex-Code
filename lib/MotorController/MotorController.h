#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include <Motor.h>
#include <Defines.h>
#include <Common.h>
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
