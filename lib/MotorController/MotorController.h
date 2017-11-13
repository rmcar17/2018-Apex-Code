#include <Motor.h>
#include <Defines.h>

class MotorController {
  public:
    MotorController();

    void MoveDirection(int angle, int speed);
}
