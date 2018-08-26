#ifndef ORBIT_H
#define ORBIT_H

#include <Common.h>
#include <Kicker.h>
#include <Timer.h>
#include <PID.h>
#include <Debug.h>
#include <Defines.h>
#include <Pins.h>
#include <Role.h>
#include <MoveData.h>
#include <Lidar.h>

extern LIDAR lidars;

class Orbit{
  public:
    Orbit();

    void setup();

    void setRole(Role _role);
    void setBallData(Vector ballData);
    void setGoalData(Vector aGoal, Vector dGoal);
    void setCompAngle(int heading);
    void setCoords(Vector coords);
    void setLightGate(bool gateVal);

    MoveData getMoveData();
    Vector getBallPos();

    void calculateCoordinates();

    void calculateMoveData();
    void calculateRotation();
    void manageKicker();
    void calculateLine();
    void avoidLine();

    void setLightValue(double angle, int tempDanger);

    void setBall(Vector tempBall);

    void resetAllData();
  private:
    void calcAttacker();
    void calcDefender();

    void calcSmallOrbit();
    void calcBigOrbit();

    void calcCloseOrbit();
    void calcTangentOrbit();

    void moveToPos(Vector position);

    bool inRange(double value, double target, int range);

    Kicker kicker;

    Timer centreDelay = Timer(CENTRE_TIME);
    Timer rememberTimer = Timer(100);
    Timer yankTimer = Timer(100);

    Role role = Role::undecided;

    Vector prevBall = Vector(0, 0);
    Vector ball = Vector(0, 0);
    Vector attackGoal = Vector(0, 0);
    Vector defendGoal = Vector(0, 0);

    Vector robotPosition = Vector(0, 0);
    Vector ballPosition = Vector(0, 0);
    Vector robotGoalPosition = Vector(0, 0, false);

    MoveData movement = {-1, 0, 0};

    int compAngle = -1;

    PID rotation = PID(ROTATION_KP, ROTATION_KI, ROTATION_KD);
    PID goalRotation = PID(GOAL_KP,GOAL_KI,GOAL_KD);

    PID horizontalMovement = PID(POS_HOR_KP, POS_HOR_KI, POS_HOR_KD);
    PID verticalMovement = PID(POS_VER_KP, POS_VER_KI, POS_VER_KD);

    PID goalieSpeed = PID(GOALIE_KP,GOALIE_KI,GOALIE_KD);

    double lineAngle = 0;
    int danger = 0;
    double prevAngle;

    double PERM = 0;
    bool hasBall, front;
    int flag = 0;
    bool canCharge = false;
    bool yank = false;
};


#endif
