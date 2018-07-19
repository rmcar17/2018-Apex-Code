#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setup(){
  kicker.setup();
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

void Orbit::setLightGate(bool gateVal){
  hasBall = gateVal;
  if(hasBall){
    ball = Vector(10,0);
  }
}

void Orbit::setCoords(Vector coords){
  robotPosition = coords;
  ballPosition = coords + ball;
 }

Vector Orbit::getBallPos(){
  return ballPosition;
}

MoveData Orbit::getMoveData(){
  return movement;
}

void Orbit::setBall(Vector tempBall){
  ball = tempBall;
}

void Orbit::calculateMoveData(){
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
    if(role == Role::attack && attackGoal.exists() && ball.exists() && ball.between(360-SMALL_ORBIT, SMALL_ORBIT) && ball.mag < 550){
      attackGoal.arg = (360-attackGoal.arg);
      rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg : -(360 - attackGoal.arg));
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
    if(ball.arg < SMALL_ORBIT || ball.arg > (360-SMALL_ORBIT)){
      movement.angle = ball.arg;
    }
    else if(ball.mag < IN_DISTANCE && (ball.arg < BIG_ORBIT || ball.arg > (360-BIG_ORBIT))){
      if(ball.arg <= 180){
        double closeness = (ball.arg-SMALL_ORBIT)/(BIG_ORBIT-SMALL_ORBIT);
        movement.angle = ball.arg+90*closeness;
      }
      else{
        double closeness = ((360-ball.arg)-SMALL_ORBIT)/(BIG_ORBIT-SMALL_ORBIT);
        movement.angle = ball.arg-90*closeness;
      }
    }
    else if(ball.mag < ORBIT_DISTANCE){
      if(ball.arg <= 180){
        movement.angle = ball.arg+90;
      }
      else{
        movement.angle = ball.arg-90;
      }
    }
    else{
      int tangentAngle = abs(round(toDegrees(asin(ORBIT_DISTANCE/ball.mag))));
      movement.speed = NORMAL_SPEED;
      movement.angle = ball.arg + tangentAngle * (ball.arg < 180 ? 1 : -1);
    }
  }
}

void Orbit::calcDefender(){
  int errorRange = 30;
  if(flag==0){
    if(!(inRange(robotPosition.i,NEUTRAL_BACK_LEFT.i,errorRange)&&inRange(robotPosition.j,NEUTRAL_BACK_LEFT.j,errorRange))){
      moveToPos(NEUTRAL_BACK_LEFT);
    } else{
      flag = 1;
    }
  }
  if(flag==1){
    if(!(inRange(robotPosition.i,NEUTRAL_FORWARD_LEFT.i,errorRange)&&inRange(robotPosition.j,NEUTRAL_FORWARD_LEFT.j,errorRange))){
      moveToPos(NEUTRAL_FORWARD_LEFT);
    } else{
      flag = 0;
    }
  }
  if(flag==2){
    if(!(inRange(robotPosition.i,NEUTRAL_FORWARD_RIGHT.i,errorRange)&&inRange(robotPosition.j,NEUTRAL_FORWARD_RIGHT.j,errorRange))){
      moveToPos(NEUTRAL_FORWARD_RIGHT);
    } else{
      flag = 3;
    }
  }
  if(flag==3){
    if(!(inRange(robotPosition.i,NEUTRAL_BACK_RIGHT.i,errorRange)&&inRange(robotPosition.j,NEUTRAL_BACK_RIGHT.j,errorRange))){
      moveToPos(NEUTRAL_BACK_RIGHT);
    } else{
      flag = 0;
    }
  }
  Serial.println(flag);


  // if(ball.exists()){
  //   if(isAngleBetween(ball.arg, 300, 60)){
  //     moveToBall();
  //   }
  //   else{
  //     calcAttacker();
  //   }
  // }
  // else{
  //   if(robotPosition.exists()){
  //     moveToPos(GOALIE_POS);
  //   }
  // }
}

void Orbit::manageKicker(){
  if(hasBall){
    kicker.kick();
  }
}

void Orbit::calculateLine(){
  if(danger>=1){
    movement.angle = mod(lineAngle+180-compAngle,360);
    movement.speed = 255;
  }
}

void Orbit::setLightValue(double angle, int tempDanger){
  lineAngle = angle;
  danger = tempDanger;
}

bool Orbit::inRange(double value, double target, int range){
  double offset = value;
  value = 0;
  target = mod(target-offset, 360);
  if(target <= range || target >= 360-range){
    return true;
  }
  else{
    return false;
  }
}

void Orbit::calcCloseOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg < 180 ? ball.arg + 90 : ball.arg - 90;
}

void Orbit::moveToPos(Vector position){
  Vector direction = position - robotPosition;

  double horizontal = horizontalMovement.update(direction.i);
  double vertical = verticalMovement.update(direction.j);
  #if SUPERTEAM
  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -230, 230);
  #else
  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -MAX_SPEED, MAX_SPEED);
  #endif
  movement.angle = mod(round(450 - toDegrees(atan2(vertical,horizontal))), 360);
}

void Orbit::moveToBall(){
  double horizontal = goalieHorizontal.update(ball.arg < 180 ? ball.arg : -(360 - ball.arg));
  // double horizontal = abs(ball.i) < 200 ? ball.i : goalieHorizontal.update(ball.i);
  double vertical = goalieVertical.update((GOALIE_POS - robotPosition).j);

  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -255, 255);
  movement.angle = mod(450 - toDegrees(atan2(vertical,horizontal)), 360);
}

void Orbit::resetAllData(){
  kicker.resetKicker();

  role = Role::undecided;
  ball = Vector(0, 0);
  attackGoal = Vector(0, 0);
  defendGoal = Vector(0, 0);
  robotPosition = Vector(0, 0);
  ballPosition = Vector(0, 0);
  compAngle = -1;
  movement = {-1, 0, 0};
}
