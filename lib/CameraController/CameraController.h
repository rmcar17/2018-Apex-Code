#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <Camera.h>
#include <Common.h>
#include <Defines.h>
#include <Vector.h>
#include <Image.h>

class CameraController {
  public:
    CameraController();

    void setup();
    void update();

    void calculateEntities();

    Vector getAttackGoal();
    Vector getDefendGoal();
    Vector getBall();
  private:
    void calculateGoals(Image aGoal, Image dGoal);
    void calculateBall(Image ballImage);

    int calculateAngle(int x, int y);

    double calculateDistance(int x, int y);
    double calculateCircleDistance(double distance);
    double calculateConeDistance(double distance);
    Camera camera = Camera();

    Vector attackGoal; //attacking goal
    Vector defendGoal; //defending goal
    Vector ball;
};

#endif
