#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Pins.h>
#include <Image.h>
#include <PlayMode.h>

class Camera{
  public:
    Camera();

    void setup();
    void update();

    Image getAttackGoal();
    Image getDefendGoal();
    Image getBall();
  private:
    PlayMode isBlueAttack();
    PlayMode blueAttack = PlayMode::undecided;

    int camBuffer[CAM_BUFFER_NUM] = {0};
    Image blueGoal;
    Image yellowGoal;
    Image ball;
};

#endif
