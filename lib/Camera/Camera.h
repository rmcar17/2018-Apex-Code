#ifndef CAMERA_H
#define CAMERA_H

#include <Image.h>

class Camera{
  public:
    Camera();

    void setup();
    void update();
  private:
    Image attackGoal;
    Image defendGoal;
    Image ball;
};

#endif
