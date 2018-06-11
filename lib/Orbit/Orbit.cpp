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
  Vector actualAttackGoal = Vector(attackGoal.mag, mod(90 + (360 - (attackGoal.arg+compAngle)),360));
  Vector actualDefendGoal = Vector(defendGoal.mag, mod(90 + (360 - (defendGoal.arg+compAngle)),360));
  // if(!(attackGoal.exists() || defendGoal.exists())){
  //   robotPosition = Vector(0, 0);
  //   ballPosition = Vector(0, 0);
  //   return;
  // }
  // if(attackGoal.exists() && defendGoal.exists()){
  //   robotPosition = (ATTACK_GOAL - actualAttackGoal + DEFEND_GOAL - actualDefendGoal) / 2;
  // }
  if(attackGoal.exists()){
    robotPosition = ATTACK_GOAL - actualAttackGoal;
  }
  // else {
  //   robotPosition = DEFEND_GOAL - actualDefendGoal;
  // }
  // Serial.print(robotPosition.i);
  // Serial.print("\t");
  // Serial.println(robotPosition.j);
  ballPosition = robotPosition + ball;
}

void Orbit::calculateMoveData(){
  calculateCoordinates();
  if(role == Role::attack){
    calcAttacker();
  }
  else{
    calcDefender();
  }
  #if DEBUG_ORBIT
    Serial.print("BALL ANGLE: ");
    Serial.print(ball.arg);
    Serial.print(" BALL DISTANCE ");
    Serial.print(ball.mag);
    Serial.print("  MOVE ANGLE: ");
    Serial.println(movement.angle);
  #endif
}

void Orbit::calculateRotation(){
  double rotate = 0;
  #if GOAL_TRACK
    if(role == Role::attack && attackGoal.exists()){
      attackGoal.arg = (360-attackGoal.arg);
      rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg : -(360 - attackGoal.arg));
    }
    else if(role == Role::defend && defendGoal.exists()){

    }
    else{
      rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
    }
  #else
      rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
  #endif
  movement.rotation = round(rotate);
}

void Orbit::calcAttacker(){
  if(ball.exists()){
    if(ball.between(360 - SMALL_ORBIT, SMALL_ORBIT)){
      calcSmallOrbit();
    }
    else if(ball.between(360 - BIG_ORBIT, BIG_ORBIT)){
      calcBigOrbit();
    }
    else if(ball.between(360 - SIDEWAYS_ORBIT, SIDEWAYS_ORBIT)){
      calcSideOrbit();
    }
    else if(ball < FAR_ORBIT){
      if(ball < CLOSE_ORBIT){
        calcCloseOrbit();
      }
      else{
        calcMediumOrbit();
      }
    }
    else{
      calcFarOrbit();
    }
  }
  else{
    if(robotPosition.exists()){
      // centre();
    }
    //If can't see goal or ball, the robot
    //can't do anything so just compass correct
  }
}

void Orbit::calcDefender(){
  moveToPos(DEFEND_GOAL);
  // if(ball.exists()){
  //   if(defendGoal.exists()){
  //     if(isAngleBetween(ball.angle, 270, 90)){
  //       moveToBall();
  //     }
  //     else{
  //       //Orbit around the ball normally
  //       calcAttacker();
  //     }
  //   }
  //   else {
  //     calcAttacker(); //Might try out some better logic here later
  //   }
  // }
  // else{
  //   if(defendGoal.exists()){
  //     centre();
  //   }
  //   //If can't see goal or ball, the robot
  //   //can't do anything so just compass correct
  // }
}

void Orbit::calcSmallOrbit(){
  movement.speed = round((1-(SMALL_ORBIT-(ball.arg < 180 ? ball.arg : 360 - ball.arg))/SMALL_ORBIT)*(MAX_SPEED-NORMAL_SPEED)+NORMAL_SPEED);
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

  movement.speed = NORMAL_SPEED;
  movement.angle = finalAngle;
}

void Orbit::calcSideOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg < 180 ? 90 : 270;
}

void Orbit::calcCloseOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg < 180 ? ball.arg + 90 : ball.arg - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (FAR_ORBIT - ball).mag / (FAR_ORBIT - CLOSE_ORBIT).mag;
  int angleBuffer = round(closeness * 90);

  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg + (ball.arg < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg;
}

void Orbit::moveToPos(Vector position){
  Vector direction = position - robotPosition;

  movement.speed = NORMAL_SPEED;
  movement.angle = mod(round(toDegrees(direction.arg)-compAngle-90),360);
}

void Orbit::moveToBall(){
  //Won't work when comparing
  //TSOPs to camera
  double correctedVerticalDistance = attackGoal.mag * cos(toRadians(compAngle + attackGoal.arg)) + CENTRE_DEFENDER_DISTANCE;
  double correctedHorizontalDistance = ball.between(360 - DEFEND_SMALL_ANGLE, DEFEND_SMALL_ANGLE) ? 0 : ball.mag * sin(toRadians(ball.arg + compAngle));

  movement.speed = NORMAL_SPEED;
  movement.angle = mod(round(toDegrees(atan2(correctedVerticalDistance,correctedHorizontalDistance)))-compAngle,360);
}

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
