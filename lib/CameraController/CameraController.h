#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <EntityData.h>

class CameraController {
  public:
    CameraController();

    void setAttackGoal(int x, int y, int pixels);
    void setDefendGoal(int x, int y, int pixels);
    void setBall(int x, int y, int pixels);

    EntityData getAttackGoal();
    EntityData getDefendGoal();
    EntityData getBall();
  private:
    int calculateAngle(int x, int y);
    int calculateGoalDistance(int pixels);
    int calculateBallDistance(int pixels);

    EntityData attackGoal; //attacking goal
    EntityData defendGoal; //defending goal
    EntityData ball;
};

#endif
