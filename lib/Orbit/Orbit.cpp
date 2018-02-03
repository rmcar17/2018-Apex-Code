#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){
  distance = ballData.distance;
  angle = ballData.angle;

  if(distance < FAR_ORBIT){
    if(isAngleBetween(angle, SMALL_ORBIT, 360 - SMALL_ORBIT)){
      calcSmallOrbit();
    }
    else if(isAngleBetween(angle, BIG_ORBIT, 360 - BIG_ORBIT)){
      calcBigOrbit();
    }
    else if(distance > CLOSE_ORBIT){
      calcCloseOrbit();
    }
    else if(distance < FAR_ORBIT){
      calcMediumOrbit();
    }
  }
  else{
    calcFarOrbit();
  }
}

MoveData Orbit::getMoveData(){
  return Movement;
}

void Orbit::calcSmallOrbit(){
  Movement.speed = MAX_SPEED;
  Movement.angle = round(angle < 180 ? angle * ORBIT_FORWARD_ANGLE_TIGHTENER : 360 - (360 - angle) * ORBIT_FORWARD_ANGLE_TIGHTENER);
}

void Orbit::calcBigOrbit(){
  double closeness, angleBuffer;
  int finalAngle;

  if(angle < 180){
    closeness = (double) (angle - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = round(angle * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + angle * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness);
  }
  else{
    closeness = (double) ((360 - angle) - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = mod(round(360 - ((360 - angle) * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + (360 - angle) * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness)), 360);
  }

  Movement.speed = MAX_SPEED;
  Movement.angle = finalAngle;
}

void Orbit::calcCloseOrbit(){
  Movement.speed = MAX_SPEED;
  Movement.angle = angle < 180 ? angle + 90 : angle - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (double) (distance - FAR_ORBIT) / (double) (CLOSE_ORBIT - FAR_ORBIT);
  int angleBuffer = round(closeness * 90);

  Movement.speed = MAX_SPEED;
  Movement.angle = angle + (angle < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  Movement.speed = MAX_SPEED;
  Movement.angle = angle;
}

void Orbit::resetMoveData(int dir = -1, int speed = 0, int rot = 0){
  Movement = {dir, speed, rot};
}
