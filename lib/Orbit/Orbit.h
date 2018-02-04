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

    void setBallData(BallData ballData);
    void setGoalData(GoalData goalData);
    void setCompAngle(int heading);
    MoveData getMoveData();

    void calculateMoveData();
    void calculateRotation();
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

    double compAngle;
    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
};

#endif
