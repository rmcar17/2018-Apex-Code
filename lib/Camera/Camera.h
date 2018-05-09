#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Debug.h>
#include <Pins.h>
#include <Image.h>
#include <Role.h>

class Camera{
  public:
    Camera();

    void setup();
    void update();

    Image getAttackGoal();
    Image getDefendGoal();
    Image getBall();
  private:
    Role isBlueAttack();
    Role blueAttack = Role::undecided;

    int camBuffer[CAM_BUFFER_NUM] = {0};
    Image blueGoal;
    Image yellowGoal;
    Image ball;
};

#endif
