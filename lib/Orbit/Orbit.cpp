#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setBallData(BallData ballData){
  ball = ballData;
}

void Orbit::setGoalData(GoalData goalData){
  goal = goalData;
}

void Orbit::setCompAngle(int heading){
  compAngle = heading;
}

MoveData Orbit::getMoveData(){
  return movement;
}

void Orbit::calculateMoveData(){
  if(ball.visible){
    if(ball.distance < FAR_ORBIT){
      if(isAngleBetween(ball.angle, SMALL_ORBIT, 360 - SMALL_ORBIT)){
        calcSmallOrbit();
      }
      else if(isAngleBetween(ball.angle, BIG_ORBIT, 360 - BIG_ORBIT)){
        calcBigOrbit();
      }
      else if(ball.distance > CLOSE_ORBIT){
        calcCloseOrbit();
      }
      else if(ball.distance < FAR_ORBIT){
        calcMediumOrbit();
      }
    }
    else{
      calcFarOrbit();
    }
  }
  else{

  }
}

void Orbit::calculateRotation(){
  double rotate;

  if(goal.visible){
    rotate = rotation.update(goal.angle < 180 ? goal.angle : -(360 - goal.angle));
  }
  else{
    rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
  }

  movement.rotation = round(rotate);
}

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = round(ball.angle < 180 ? ball.angle * ORBIT_FORWARD_ANGLE_TIGHTENER : 360 - (360 - ball.angle) * ORBIT_FORWARD_ANGLE_TIGHTENER);
}

void Orbit::calcBigOrbit(){
  double closeness, angleBuffer;
  int finalAngle;

  if(ball.angle < 180){
    closeness = (double) (ball.angle - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = round(ball.angle * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + ball.angle * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness);
  }
  else{
    closeness = (double) ((360 - ball.angle) - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = mod(round(360 - ((360 - ball.angle) * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + (360 - ball.angle) * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness)), 360);
  }

  movement.speed = MAX_SPEED;
  movement.angle = finalAngle;
}

void Orbit::calcCloseOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.angle < 180 ? ball.angle + 90 : ball.angle - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (double) (ball.distance - FAR_ORBIT) / (double) (CLOSE_ORBIT - FAR_ORBIT);
  int angleBuffer = round(closeness * 90);

  movement.speed = MAX_SPEED;
  movement.angle = ball.angle + (ball.angle < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.angle;
}

void Orbit::resetAllData(){
  ball = {-1, 0, false};
  goal = {-1, 0, false};
  movement = {-1, 0, 0};
}
