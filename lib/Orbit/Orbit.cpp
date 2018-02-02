#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::calculateMoveData(BallData ballData){

}

MoveData Orbit::getMoveData(){
  return Movement;
}

void Orbit::resetMoveData(int dir = -1, int speed = 0, int rot = 0){
  Movement = {dir, speed, rot};
}
