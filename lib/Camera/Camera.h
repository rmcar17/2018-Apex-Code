#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Timer.h>
#include <Pins.h>
#include <Image.h>
#include <Role.h>
#include <Debug.h>

class Camera{
  public:
    Camera();

    void setup();
    void update();

    Image getAttackGoal();
    Image getDefendGoal();
    Image getBall();
  private:
    Timer cameraTimer = Timer(CAMERA_UPDATE_TIME);
    Role isBlueAttack();
    Role blueAttack = Role::undecided;

    int camBuffer[CAM_BUFFER_NUM] = {0};
    Image blueGoal;
    Image yellowGoal;
    Image ball;
};

#endif
