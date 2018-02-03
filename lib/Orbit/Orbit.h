#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <Defines.h>
#include <BallData.h>
#include <MoveData.h>

class Orbit{
  public:
    Orbit();
    MoveData getMoveData();
    void calculateMoveData(BallData ballData);
    void avoidLine();
    void setRotation(int rotation);
    void resetMoveData(int dir = -1, int speed = 0, int rot = 0);
  private:
    void getCloseOrbit();
    void getMediumOrbit();
    void getFarOrbit();

    MoveData Movement = {-1, 0, 0};

    int distance, angle;
};

#endif
