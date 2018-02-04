#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <Pid.h>
#include <Defines.h>
#include <BallData.h>
#include <GoalData.h>
#include <MoveData.h>

class Orbit{
  public:
    Orbit();
    MoveData getMoveData();

    void setGoalData(GoalData goalData);
    void setBallData(BallData ballData);

    void calculateMoveData();
    void calculateRotation(int compAngle);
    void avoidLine();

    void resetMoveData(int dir = -1, int speed = 0, int rot = 0);
  private:
    void calcSmallOrbit();
    void calcBigOrbit();

    void calcCloseOrbit();
    void calcMediumOrbit();
    void calcFarOrbit();

    GoalData goal;
    BallData ball;
    MoveData movement = {-1, 0, 0};

    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
    int rotate;
};

#endif
