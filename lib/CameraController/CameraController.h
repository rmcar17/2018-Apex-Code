#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Common.h>
#include <Defines.h>
#include <EntityData.h>
#include <Image.h>

class CameraController {
  public:
    CameraController();

    void updateCamera();

    void calculateEntities();

    EntityData getAttackGoal();
    EntityData getDefendGoal();
    EntityData getBall();
  private:
    void calculateAttackGoal(Image aGoal);
    void calculateDefendGoal(Image dGoal);
    void calculateBall(Image ballImage);

    int calculateAngle(int x, int y);
    double calculateDistance(int x, int y);
    // Camera camera;

    EntityData attackGoal; //attacking goal
    EntityData defendGoal; //defending goal
    EntityData ball;
};

#endif