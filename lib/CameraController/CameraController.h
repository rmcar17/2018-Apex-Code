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


    Vector getAttackGoal();
    Vector getDefendGoal();
    Vector getBall();
  private:
    Camera camera = Camera();
    Timer cameraTimer = Timer(CAMERA_UPDATE_TIME);
    
    void calculateEntities();
    void calculateEntity(Vector *entity, Image image);

    int calculateAngle(int x, int y);

    double calculateDistance(int x, int y);
    double calculateCircleDistance(double distance);
    double calculateConeDistance(double distance);

    Vector attackGoal = Vector(0,0); //attacking goal
    Vector defendGoal = Vector(0,0); //defending goal
    Vector ball = Vector(0,0);
};

#endif
