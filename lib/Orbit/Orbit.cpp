#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setRole(Role _role){
  role = _role;
}

void Orbit::setBallData(Vector ballData){
  ball = ballData;
}

void Orbit::setGoalData(Vector aGoal, Vector dGoal){
  attackGoal = aGoal;
  defendGoal = dGoal;
}

void Orbit::setCompAngle(int heading){
  compAngle = heading;
}

MoveData Orbit::getMoveData(){
  return movement;
}

void Orbit::calculateCoordinates(){
  Vector actualAttackGoal = Vector(attackGoal.mag, attackGoal.arg + compAngle);
  Vector actualDefendGoal = Vector(defendGoal.mag, defendGoal.arg + compAngle);
  if(!(attackGoal.exists() || defendGoal.exists())){
    robotPosition = Vector(0, 0);
    ballPosition = Vector(0, 0);
    return;
  }
  if(attackGoal.exists() && defendGoal.exists()){
    robotPosition = (ATTACK_GOAL - actualAttackGoal + DEFEND_GOAL - actualDefendGoal) / 2;
  }
  else if (attackGoal.exists()){
    robotPosition = ATTACK_GOAL - actualAttackGoal;
  }
  else {
    robotPosition = DEFEND_GOAL - actualDefendGoal;
  }
  ballPosition = robotPosition + ball;
}

void Orbit::calculateMoveData(){
  if(role == Role::attack){
    calcAttacker();
  }
  else{
    //calcDefender();
  }
  #if DEBUG_ORBIT
    Serial.print("BALL ANGLE: ");
    Serial.print(ball.arg);
    Serial.print("  MOVE ANGLE: ");
    Serial.println(movement.angle);
  #endif
}

void Orbit::calculateRotation(){
  double rotate;
  // if(attackGoal.visible){
  //   if(role == Role::attack){
  //   rotate = rotation.update(attackGoal.angle < 180 ? attackGoal.angle : -(360 - attackGoal.angle));
  //   }
  //   else{
  //     double oppositeAngle = mod(attackGoal.angle + 180, 360);
  //     rotate = rotation.update(oppositeAngle < 180 ? oppositeAngle : -(360 - oppositeAngle));
  //   }
  // }
  // else{
    rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
  // }

  movement.rotation = round(rotate);
}

void Orbit::calcAttacker(){
  if(ball.exists()){
    if(ball < FAR_ORBIT){
      if(isAngleBetween(ball.arg, 360 - SMALL_ORBIT, SMALL_ORBIT)){
        calcSmallOrbit();
      }
      else if(isAngleBetween(ball.arg, 360 - BIG_ORBIT, BIG_ORBIT)){
        calcBigOrbit();
      }
      else if(ball < CLOSE_ORBIT){
        calcCloseOrbit();
      }
      else if(ball < FAR_ORBIT){
        calcMediumOrbit();
      }
    }
    else{
      calcFarOrbit();
    }
  }
  else{
    if(robotPosition.exists()){
      //centre();
    }
    //If can't see goal or ball, the robot
    //can't do anything so just compass correct
  }
}

// void Orbit::calcDefender(){
//   if(ball.visible){
//     if(attackGoal.visible){
//       if(isAngleBetween(ball.angle, 270, 90)){
//         moveToBall();
//       }
//       else{
//         //Orbit around the ball normally
//         calcAttacker();
//       }
//     }
//     else {
//       calcAttacker(); //Might try out some better logic here later
//     }
//   }
//   else{
//     if(attackGoal.visible){
//       centre();
//     }
//     //If can't see goal or ball, the robot
//     //can't do anything so just compass correct
//   }
// }

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = round(ball.arg < 180 ? ball.arg * ORBIT_FORWARD_ANGLE_TIGHTENER : 360 - (360 - ball.arg) * ORBIT_FORWARD_ANGLE_TIGHTENER);
}

void Orbit::calcBigOrbit(){
  double closeness, angleBuffer;
  int finalAngle;

  if(ball.arg < 180){
    closeness = (double) (ball.arg - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = round(ball.arg * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + ball.arg * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness);
  }
  else{
    closeness = (double) ((360 - ball.arg) - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = mod(round(360 - ((360 - ball.arg) * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + (360 - ball.arg) * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness)), 360);
  }

  movement.speed = MAX_SPEED;
  movement.angle = finalAngle;
}

void Orbit::calcCloseOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.arg < 180 ? ball.arg + 90 : ball.arg - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (FAR_ORBIT - ball).mag / (FAR_ORBIT - CLOSE_ORBIT).mag;
  int angleBuffer = round(closeness * 90);

  movement.speed = MAX_SPEED;
  movement.angle = ball.arg + (ball.arg < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.arg;
}

void Orbit::centre(){
  Vector centre = CENTRE - robotPosition;

  movement.speed = MAX_SPEED; // Add PID for speed
  movement.angle = mod(round(centre.arg-compAngle),360);
}

// void Orbit::moveToBall(){
//   //Won't work when comparing
//   //TSOPs to camera
//   double correctedVerticalDistance = attackGoal.distance * cos(toRadians(compAngle + attackGoal.angle)) + CENTRE_DEFENDER_DISTANCE;
//   double correctedHorizontalDistance = isAngleBetween(ball.angle, 360 - DEFEND_SMALL_ANGLE, DEFEND_SMALL_ANGLE) ? 0 : ball.distance * sin(toRadians(ball.angle + compAngle));
//
//   movement.speed = MAX_SPEED;
//   movement.angle = mod(round(toDegrees(atan2(correctedVerticalDistance,correctedHorizontalDistance)))-compAngle,360);
// }

void Orbit::resetAllData(){
  role = Role::undecided;
  ball = Vector(0, 0);
  ballPosition = Vector(0, 0);
  attackGoal = Vector(0, 0);
  defendGoal = Vector(0, 0);
  robotPosition = Vector(0, 0);
  compAngle = -1;
  movement = {-1, 0, 0};
}
