#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <EntityData.h>
#include <Image.h>

class CameraController {
  public:
    CameraController();

    void setAttackGoal(Image aGoal);
    void setDefendGoal(Image dGoal);
    void setBall(Image ballImage);

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
