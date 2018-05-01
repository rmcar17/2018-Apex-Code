#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <Pid.h>
#include <Debug.h>
#include <Defines.h>
#include <PlayMode.h>
#include <EntityData.h>
#include <MoveData.h>

class Orbit{
  public:
    Orbit();

    void setRole(PlayMode playMode);
    void setBallData(Vector ballData);
    void setGoalData(Vector aGoal, Vector dGoal);
    void setCompAngle(int heading);
    MoveData getMoveData();

    void calculateMoveData();
    void calculateRotation();
    void avoidLine();

    void resetAllData();
  private:
    void calcAttacker();
    void calcDefender();

    void calcSmallOrbit();
    void calcBigOrbit();

    void calcCloseOrbit();
    void calcMediumOrbit();
    void calcFarOrbit();

    void centre();
    void moveToBall();

    PlayMode role = PlayMode::undecided;

    Vector ball = Vector(-1,-1);
    Vector attackGoal = Vector(-1,-2);
    Vector defendGoal = Vector(-1,-2);
    MoveData movement = {-1, 0, 0};

    double compAngle = 0;
    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
};

#endif
