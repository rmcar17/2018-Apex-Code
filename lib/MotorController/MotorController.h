#include <Motor.h>
#include <Defines.h>
#include <Common.h>

class MotorController {
  public:
    MotorController();

    void MoveDirection(int angle, int speed, int rotation);
};
