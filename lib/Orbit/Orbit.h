#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <Pid.h>
#include <Debug.h>
#include <Defines.h>
#include <Role.h>
#include <MoveData.h>

class Orbit{
  public:
    Orbit();

    void setRole(Role _role);
    void setBallData(Vector ballData);
    void setGoalData(Vector aGoal, Vector dGoal);
    void setCompAngle(int heading);
    MoveData getMoveData();

    void calculateCoordinates();

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

    Role role = Role::undecided;

    Vector ball = Vector(0, 0);
    Vector attackGoal = Vector(0, 0);
    Vector defendGoal = Vector(0, 0);

    Vector robotPosition = Vector(0, 0);
    Vector ballPosition = Vector(0, 0);

    MoveData movement = {-1, 0, 0};

    int compAngle = -1;
    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
};

#endif
