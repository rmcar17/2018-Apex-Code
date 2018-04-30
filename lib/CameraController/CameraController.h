#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <Camera.h>
#include <Common.h>
#include <Defines.h>
#include <EntityData.h>
#include <Image.h>

class CameraController {
  public:
    CameraController();

    void cameraSetup();
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
    double calculateCircleDistance(double distance);
    double calculateConeDistance(double distance);
    Camera camera = Camera();

    EntityData attackGoal; //attacking goal
    EntityData defendGoal; //defending goal
    EntityData ball;
};

#endif
