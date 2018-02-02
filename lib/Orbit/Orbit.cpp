#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){
  distance = ballData.distance;
  direction = ballData.angle;

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
  Movement.angle = direction < 180 ? direction + 90 : direction - 90;
}

void Orbit::resetMoveData(int dir = -1, int speed = 0, int rot = 0){
  Movement = {dir, speed, rot};
}
