#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include <Motor.h>
#include <Defines.h>
#include <Common.h>

class MotorController {
  public:
    MotorController();

    void MoveDirection(int angle, int speed, int rotation);
};
#endif
