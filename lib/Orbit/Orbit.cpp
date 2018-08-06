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
  robotGoalPosition = Vector(robotPosition.i,abs(defendGoal.j),false);
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
    if(role == Role::attack && attackGoal.exists() && ball.exists() && ball.between(360-SMALL_ORBIT-30, SMALL_ORBIT+30) && ball.mag < 200){
      attackGoal.arg = (360-attackGoal.arg);
      rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg : -(360 - attackGoal.arg))*3;
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
    rememberTimer.update();
  }
  else if(!rememberTimer.hasTimePassedNoUpdate()){
    ball = prevBall;
  }


  if(ball.exists()){
    centreDelay.update();
    if(ball.arg < SMALL_ORBIT || ball.arg > (360-SMALL_ORBIT)){
      calcSmallOrbit(); // Moves directly to the ball
    }
    else if(/*ball.mag < IN_DISTANCE &&*/ (ball.arg < BIG_ORBIT || ball.arg > (360-BIG_ORBIT))){
      calcBigOrbit(); // Transfers between close orbit and small orbit
      if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
        movement.speed = round(movement.speed * SLOW_SPEED);
      }
    }
    else if(ball.mag < ORBIT_DISTANCE){
      calcCloseOrbit(); // Moves perpendicular to the ball
      if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
        movement.speed = round(movement.speed * SLOW_SPEED);
      }
    }
    else{
      calcTangentOrbit(); // Enters the ball's nearest tangent
      if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
        movement.speed = round(movement.speed * SLOW_SPEED);
      }
    }
  }
  else{
    if(centreDelay.hasTimePassedNoUpdate()){
      moveToPos(CENTRE); // Haven't seen the ball for too long, move to centre
    }
  }

  // Boss Logic
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500){
    moveToPos(CENTRE);
  }
}

void Orbit::calcDefender(){
  if(ball.exists()){
    if(abs(defendGoal.j)>600){
      canCharge = false;
    }
    if(abs(defendGoal.j)>350){
      if(abs(ball.i-robotPosition.i)<50){
        moveToGoalPos(Vector(robotPosition.i,200,false));
      } else{
        moveToGoalPos(Vector(constrain(ball.i > 0 ? FIELD_WIDTH : 0,800,1200),200,false));
      }
    } else{
      canCharge = true;
      if(abs(ball.i-robotPosition.i)<50){
        // Stay where we are
        moveToGoalPos(Vector(robotPosition.i,robotPosition.j,false));
      } else{
        moveToGoalPos(Vector(constrain(ball.i > 0 ? FIELD_WIDTH : 0,800,1200),robotGoalPosition.j,false));
      }
    }
    if((ball.arg < SMALL_ORBIT || ball.arg > (360-SMALL_ORBIT)) && canCharge){
      movement.angle = ball.arg;
      movement.speed = NORMAL_SPEED;
    }
  } else if(abs(defendGoal.j)>350){
    moveToGoalPos(Vector(GOALIE_POS.i,200,false));
  } else{
    moveToGoalPos(Vector(GOALIE_POS.i,robotGoalPosition.j,false));
  }
}

void Orbit::manageKicker(){
  if(hasBall){
    kicker.kick();
  }
}

void Orbit::calcSmallOrbit(){
  movement.speed = NORMAL_SPEED;
  movement.angle = (ball.arg < 180 ? ball.arg*ANGLE_TIGHTENER : 360-(360-ball.arg)*ANGLE_TIGHTENER);
}

void Orbit::calcBigOrbit(){
  movement.speed = NORMAL_SPEED;
  if(ball.arg <= 180){
    double closeness = (ball.arg-SMALL_ORBIT)/(BIG_ORBIT-SMALL_ORBIT);
    movement.angle = ball.arg+(90*closeness)*(ball.mag > SKEW_DISTANCE ? BIG_SKEWER : 1);
  }
  else{
    double closeness = ((360-ball.arg)-SMALL_ORBIT)/(BIG_ORBIT-SMALL_ORBIT);
    movement.angle = ball.arg-(90*closeness)*BIG_SKEWER;
  }
}

void Orbit::calcCloseOrbit(){
  movement.speed = round(NORMAL_SPEED*(ball.mag < SLOW_DISTANCE ? BIG_SLOWER : 1));
  movement.angle = ball.arg < 180 ? ball.arg + 90 : ball.arg - 90;
}

void Orbit::calcTangentOrbit(){
  int tangentAngle = abs(round(toDegrees(asin(ORBIT_DISTANCE/ball.mag))));
  movement.speed = round(NORMAL_SPEED*(ball.mag < SLOW_DISTANCE ? BIG_SLOWER : 1));
  movement.angle = ball.arg + tangentAngle * (ball.arg < 180 ? 1 : -1);
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

void Orbit::moveToGoalPos(Vector position){
  Vector direction = position - robotGoalPosition;

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

  if(ball.exists()){
    prevBall = ball;
  }
  role = Role::undecided;
  ball = Vector(0, 0);
  attackGoal = Vector(0, 0);
  defendGoal = Vector(0, 0);
  robotPosition = Vector(0, 0);
  ballPosition = Vector(0, 0);
  compAngle = -1;
  movement = {-1, 0, 0};
}
