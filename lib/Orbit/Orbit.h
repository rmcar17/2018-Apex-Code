#ifndef ORBIT_H
#define ORBIT_H

#include <BallData.h>
#include <MoveData.h>

class Orbit{
  public:
    Orbit();
    MoveData getMoveData();
    void calculateMoveData(BallData ballData);
    void avoidLine();
    void setRotation(int rotation);
    void resetMoveData(int direction = -1, int speed = 0, int rotation = 0);
  private:
    MoveData getCloseOrbit(int direction);
    MoveData getMediumOrbit(int direction, int distance);
    MoveData getFarOrbit(int direction);

    MoveData Movement = {-1, 0, 0};
};

#endif
