#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){
  if(ballData.visible){
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
  else{

  }
}

void Orbit::calculateRotation(int compAngle, int goalAngle){
  //This section will change when a
  //goalData object is created, or
  //when programming the defender.
  //More methods will likely be created.

  if(goalAngle != -1){
    rotate = rotation.update(goalAngle < 180 ? goalAngle : -(360 - goalAngle));
  }
  else{
    rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - goalAngle));
  }
  movement.rotation = rotate;
}

MoveData Orbit::getMoveData(){
  return movement;
}

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = round(angle < 180 ? angle * ORBIT_FORWARD_ANGLE_TIGHTENER : 360 - (360 - angle) * ORBIT_FORWARD_ANGLE_TIGHTENER);
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

  movement.speed = MAX_SPEED;
  movement.angle = finalAngle;
}

void Orbit::calcCloseOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = angle < 180 ? angle + 90 : angle - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (double) (distance - FAR_ORBIT) / (double) (CLOSE_ORBIT - FAR_ORBIT);
  int angleBuffer = round(closeness * 90);

  movement.speed = MAX_SPEED;
  movement.angle = angle + (angle < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = angle;
}

void Orbit::resetMoveData(int dir, int speed, int rot){
  movement = {dir, speed, rot};
}
