#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){
  distance = ballData.distance;
  angle = ballData.angle;

  if(distance > CLOSE_ORBIT){
    getCloseOrbit();
  }
  else if(distance < FAR_ORBIT){

  }
  else{

  }
}

MoveData Orbit::getMoveData(){
  return Movement;
}

void Orbit::getCloseOrbit(){
  Movement.speed = SPEED;
  Movement.angle = angle < 180 ? angle + 90 : angle - 90;
}

void Orbit::resetMoveData(int dir = -1, int speed = 0, int rot = 0){
  Movement = {dir, speed, rot};
}
