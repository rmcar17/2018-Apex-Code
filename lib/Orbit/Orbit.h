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

    void setBallData(BallData ballData);
    void setGoalData(GoalData goalData);

    void calculateMoveData();
    void calculateRotation(int compAngle);
    void avoidLine();

    void resetAllData();
  private:
    void calcSmallOrbit();
    void calcBigOrbit();

    void calcCloseOrbit();
    void calcMediumOrbit();
    void calcFarOrbit();

    BallData ball = {-1, 0, false};
    GoalData goal = {-1, 0, false};
    MoveData movement = {-1, 0, 0};

    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
    int rotate;
};

#endif
