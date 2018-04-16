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
    Image attackGoal;
    Image defendGoal;
    Image ball;
};

#endif
