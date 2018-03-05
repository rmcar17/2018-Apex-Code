#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <EntityData.h>

class CameraController {
  public:
    CameraController();

    void setAttackGoal(int x, int y, int pixels);
    void setDefendGoal(int x, int y, int pixels);
    void setBall(int x, int y, int pixels);

    int calculateAngle(int x, int y);
    int calculateDistance(int pixels);

    EntityData getAttackGoal();
    EntityData getDefendGoal();
    EntityData getBall();
  private:
    EntityData aGoal; //attacking goal
    EntityData dGoal; //defending goal
    EntityData ball;
};

#endif
