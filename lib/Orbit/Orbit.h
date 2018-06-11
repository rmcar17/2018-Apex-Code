#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <PID.h>
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
    void setCoords(Vector coords);
    MoveData getMoveData();

    void calculateMoveData();
    void calculateRotation();
    void calculateLine();
    void avoidLine();

    void setLightValue(double angle, int tempDanger);

    void resetAllData();
  private:
    void calcAttacker();
    void calcDefender();

    void calcSmallOrbit();
    void calcBigOrbit();
    void calcSideOrbit();

    void calcCloseOrbit();
    void calcMediumOrbit();
    void calcFarOrbit();

    void moveToPos(Vector position);
    void moveToBall();

    bool inRange(double value, double target, int range);

    Role role = Role::undecided;

    Vector ball = Vector(0, 0);
    Vector attackGoal = Vector(0, 0);
    Vector defendGoal = Vector(0, 0);

    Vector robotPosition = Vector(0, 0);
    Vector ballPosition = Vector(0, 0);

    MoveData movement = {-1, 0, 0};

    int compAngle = -1;
    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
    PID goalRotation = PID(GOAL_KP,GOAL_KI,GOAL_KD);

    double lineAngle = 0;
    int danger = 0;
};


#endif
