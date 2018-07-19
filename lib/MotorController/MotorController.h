#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <Motor.h>
#include <Common.h>
#include <MoveData.h>
#include <Defines.h>
#include <Pins.h>

class MotorController {
  public:
    MotorController();

    void motorSetup();

    void moveDirection(MoveData movement);
    void rotate(int rotation);
    void move(int FR, int BR, int BL, int FL);
    void brake();

  private:
    Motor motorFR, motorBR, motorBL, motorFL;
};
#endif
