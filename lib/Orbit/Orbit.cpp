#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setRole(PlayMode playMode){
  role = playMode;
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

// void calculateCoordinates(){
//   Vector actualAttackGoal = Vector(attackGoal.mag,attackGoal.arg + compAngle);
//   if(!(attackGoal.exists() || defendGoal.exists())){
//     robotPosition = Vector(0, 0);
//     ballPosition = Vector(0, 0);
//     return;
//   }
//   if(attackGoal.exists() && defendGoal.exists()){
//     robotPosition = (ATTACK_GOAL - attackGoal + DEFEND_GOAL - defendGoal) / 2;
//   }
//   else if (attackGoal.exists()){
//     robotPosition = ATTACK_GOAL - attackGoal;
//   }
//   else {
//     robotPosition = DEFEND_GOAL - defendGoal;
//   }
//   ballPosition = robotPosition + ball;
// }

void Orbit::calculateMoveData(){
  if(role == PlayMode::attack){
    calcAttacker();
  }
  else{
    //calcDefender();
  }
  #if DEBUG_ORBIT
    Serial.print("BALL ANGLE: ");
    Serial.print(ball.angle);
    Serial.print("  MOVE ANGLE: ");
    Serial.println(movement.angle);
  #endif
}

// void Orbit::calculateRotation(){
//   double rotate;
//
//   if(attackGoal.visible){
//     if(role == PlayMode::attack){
//     rotate = rotation.update(attackGoal.angle < 180 ? attackGoal.angle : -(360 - attackGoal.angle));
//     }
//     else{
//       double oppositeAngle = mod(attackGoal.angle + 180, 360);
//       rotate = rotation.update(oppositeAngle < 180 ? oppositeAngle : -(360 - oppositeAngle));
//     }
//   }
//   else{
//     rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
//   }
//
//   movement.rotation = round(rotate);
// }

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
    if(attackGoal.exists()){
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

// void Orbit::centre(){
//   double goalAngle = toRadians(compAngle + attackGoal.angle);
//
//   double correctedVerticalDistance = attackGoal.distance * cos(goalAngle) + (role == PlayMode::attack ? -CENTRE_ATTACKER_DISTANCE : CENTRE_DEFENDER_DISTANCE);
//   double correctedHorizontalDistance = attackGoal.distance * sin(goalAngle);
//
//   movement.speed = MAX_SPEED;
//   movement.angle = mod(round(450 - toDegrees(atan2(correctedVerticalDistance,correctedHorizontalDistance)))-compAngle,360);
// }

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
  role = PlayMode::undecided;
  ball = Vector(0, 0);
  attackGoal = Vector(0, 0);
  defendGoal = Vector(0, 0);
  compAngle = -1;
  movement = {-1, 0, 0};
}
