#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Pins.h>
#include <Image.h>

class Camera{
  public:
    Camera();

    void setup();
    void update();

    Image getAttackGoal();
    Image getDefendGoal();
    Image getBall();
  private:
    bool isBlueAttack();
    bool blueAttack = true;

    int camBuffer[CAM_BUFFER_NUM] = {0};
    Image blueGoal;
    Image yellowGoal;
    Image ball;
};

#endif
