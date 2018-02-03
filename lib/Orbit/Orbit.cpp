#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){
  distance = ballData.distance;
  angle = ballData.angle;

  if(distance > CLOSE_ORBIT){
    calcCloseOrbit();
  }
  else if(distance < FAR_ORBIT){
    calcMediumOrbit();
  }
  else{
    calcFarOrbit();
  }
}

MoveData Orbit::getMoveData(){
  return Movement;
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
