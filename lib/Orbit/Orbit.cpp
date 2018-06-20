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
  front = ball.between(270, 90);
  if(ball.exists()){
    if(ball.between(360 - SMALL_ORBIT, SMALL_ORBIT)){
      calcSmallOrbit();
    }
    else if(ball.between(360 - BIG_ORBIT, BIG_ORBIT)){
      calcBigOrbit();
    }
    else if(ball.between(360 - SIDEWAYS_ORBIT, SIDEWAYS_ORBIT) && ball > SIDE_DISTANCE){
      calcSideOrbit();
    }
    else if(ball < (front ? FAR_ORBIT_FRONT : FAR_ORBIT_BACK)){
      if(ball < (front ? CLOSE_ORBIT_FRONT : CLOSE_ORBIT_BACK)){
        calcCloseOrbit();
      }
      else if (ball.between(360 - BETWEEN_ORBIT, BETWEEN_ORBIT)){
        calcBetweenOrbit();
      }
      else if (ball.between(360 - BACK_ORBIT, BACK_ORBIT) && ball > BACK_DISTANCE && ball < MAX_BACK_DISTANCE){
        calcStraightOrbit();
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
    #if SUPERTEAM
      if(robotPosition.exists()){
        movement.rotation = 0;
        #if ROBOT == 1
          moveToPos(CENTRE);
        #else
          moveToPos(DEFEND_GOAL);
        #endif
      }
    #endif
  }
}

void Orbit::calcDefender(){
  moveToPos(DEFEND_GOAL);
  // moveToBall();
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

void Orbit::calcBetweenOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = 180 - (ball.arg < 180 ? 90 : -90) * (1-(ball.arg < 180 ? ball.arg : (360-ball.arg) - SIDEWAYS_ORBIT) / (BETWEEN_ORBIT - SIDEWAYS_ORBIT));
}

void Orbit::calcStraightOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = 180;
}

void Orbit::calcCloseOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = ball.arg < 180 ? ball.arg + 90 : ball.arg - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = ((front ? FAR_ORBIT_FRONT : FAR_ORBIT_BACK) - ball).mag / (front ? (FAR_ORBIT_FRONT - CLOSE_ORBIT_FRONT) : (FAR_ORBIT_BACK - CLOSE_ORBIT_BACK)).mag;
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
