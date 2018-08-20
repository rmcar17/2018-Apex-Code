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
    // Serial.print(attackGoal.exists());
    // Serial.print("\t");
    // Serial.print(ball.exists());
    // Serial.print("\t");
    // Serial.print(ball.between(360-SMALL_ORBIT-30,SMALL_ORBIT+30));
    // Serial.print("\t");
    // Serial.println(ball.mag < GOAL_TRACK_DIS);
    if(role == Role::attack && attackGoal.exists() && ball.exists() && ball.between(340,20) && ball.mag < GOAL_TRACK_DIS){
      attackGoal.arg = (360-attackGoal.arg);
      rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg*1.5 : -(360 - attackGoal.arg))*1.5;
    }
    else{
      rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
    }
  #else
    rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
  #endif
  // attackGoal.arg = (360-attackGoal.arg);
  // rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg : -(360 - attackGoal.arg));
  movement.rotation = round(rotate);
}

void Orbit::calcAttacker(){
  if(ball.exists()){
    rememberTimer.update();
  }
  else if(!rememberTimer.hasTimePassedNoUpdate()){
    ball = prevBall;
  }

  if(ball.exists()&&!yank){
    centreDelay.update();
    if(ball.arg < SMALL_ORBIT+SMALL_ORBIT_RIGHT || ball.arg > (360-SMALL_ORBIT-SMALL_ORBIT_LEFT)){
      yankTimer.update();
      calcSmallOrbit(); // Moves directly to the ball
      // Serial.println("calcSmallOrbit()");
    }
    else if((ball.arg < BRAKE_ANGLE_RIGHT || ball.arg > (360-BRAKE_ANGLE_LEFT)) && ball.mag<BRAKE_DISTANCE && !yankTimer.hasTimePassedNoUpdate()){
      PERM = prevAngle + 180;
      movement.angle = PERM;
      movement.speed = NORMAL_SPEED;
      yank = true;
    }
    else{
      yankTimer.update();
      if(/*ball.mag < IN_DISTANCE &&*/ (ball.arg < BIG_ORBIT+BIG_ORBIT_RIGHT || ball.arg > (360-BIG_ORBIT-BIG_ORBIT_LEFT))){
        calcBigOrbit(); // Transfers between close orbit and small orbit
        // Serial.println("calcBigOrbit()");
        if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
          movement.speed = round(movement.speed * SLOW_SPEED-10);
        }
      }
      else if(ball.mag < ORBIT_DISTANCE){
        calcCloseOrbit(); // Moves perpendicular to the ball
        // Serial.println("calcCloseOrbit()");
        if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
          movement.speed = round(movement.speed * (SLOW_SPEED+0.2));
        }
      }
      else{
        calcTangentOrbit(); // Enters the ball's nearest tangent
        // Serial.println("calcTangentOrbit()");
        if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
          if(ball.between(TANGENT_SLOW_DOWN,360-TANGENT_SLOW_DOWN) && ball.mag<TANGENT_SLOW_DOWN_MAG){
            movement.speed = round(movement.speed * SLOW_SPEED);
            // movement.speed = round((movement.speed * SLOW_SPEED)-40*(1-constrain(ball.mag/1500,0,1)));
          }else{
            movement.speed = round(movement.speed * SLOW_SPEED);
          }
        }
      }
    }
  } else{
    if(ball.exists()){
      centreDelay.update();
      movement.angle = PERM;
      movement.speed = NORMAL_SPEED;
      yank = false;
    }
    else{
      if(centreDelay.hasTimePassedNoUpdate()){
        #if ROBOT == 1
          moveToPos(CENTRE);
        #else
          moveToPos(GOALIE_POS);
        #endif
      }
    }
  }
  prevAngle = movement.angle;

  // BOSS LOGIC
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500 && (lidars.lidarBack > 1900 || lidars.lidarBack < 400)){
    moveToPos(CENTRE);
  }
}

void Orbit::calcDefender(){
  if(ball.exists() && ballPosition.j < 800){
    calcAttacker();
  }
  else{
    moveToPos(GOALIE_POS);
  }
}

void Orbit::manageKicker(){
  if(hasBall){
    kicker.kick();
  }
}

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = (ball.arg < 180 ? ball.arg*ANGLE_TIGHTENER_RIGHT-SMALL_OFFSET_RIGHT : 360-(360-ball.arg)*ANGLE_TIGHTENER_LEFT-SMALL_OFFSET_LEFT);
  // movement.angle = (ball.arg < 180 ? ball.arg : 360-(360-ball.arg));
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
