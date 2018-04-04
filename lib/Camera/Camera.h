#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Image.h>

#define cameraSerial Serial1

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
