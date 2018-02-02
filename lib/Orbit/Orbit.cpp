#include "Orbit.h"

Orbit::Orbit(){

}

MoveData Orbit::getMoveData(){
  return Movement;
}

void Orbit::resetMoveData(int direction = -1, int speed = 0, int rotation = 0){
  Movement = {direction, speed, rotation};
}
