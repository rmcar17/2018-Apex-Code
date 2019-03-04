#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setup(){
  kicker.setup();
  bt.setup();
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
  // hasBall = gateVal;
  // if(hasBall){
  //   ball = Vector(10,0);
  // }
}

void Orbit::setCoords(Vector coords){
  robotPosition = coords;
  if(ball.exists()){
    ballPosition = coords + ball;
  }
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
    // Serial.println(attackGoal.exists());
    if(role == Role::attack && attackGoal.exists()){
      attackGoal.arg = (360-attackGoal.arg);
      double temp = modelDistance(attackGoal.mag) * ROTATION_MULTIPLIER;
      rotate = goalRotation.update(attackGoal.arg < 180 ? attackGoal.arg + temp : -(360 - attackGoal.arg + temp));
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

double Orbit::orbitSimple(int angle, double ratio){
  /* Simple orbit from last year for testing */
  if(ratio < 0.00 || ratio > 1.00){
      ratio = 1.00;
  }
  if(angle < 40 || angle > 360-40){
      movement.speed = SHOOTING_SPEED;
      return angle < 180 ? (angle - (angle * 0.5 * ratio)) : (angle - ((360 - angle) * 0.5 * ratio));
  }else{
      return angle < 180 ? (angle + (90 * ratio)) : (angle - (90 * ratio));
  }
}

double Orbit::orbit(int angle, int distance){
  if(distance > 550){
      /* Move ball direction */
      return orbitSimple(angle, 0.3);
  }else if(distance > 450 && distance <= 550){
      /* A lil bit closer */
      return orbitSimple(angle, 0.4);
  }else if(distance > 250 && distance <= 450){
      /* Almost Normal Orbit orbit */
      return orbitSimple(angle, 0.55);
  }else if(distance <= 250){
      /* More Aggressive than Normal Orbit */
      return orbitSimple(angle, 0.8);
  }
}

void Orbit::calcAttacker(){
  if(ball.exists()){
    rememberTimer.update();
    centreDelay.update();
  }
  else if(!rememberTimer.hasTimePassedNoUpdate()){
    ball = prevBall;
  }

  if(ball.exists()){
    movement.speed = NORMAL_SPEED;
    movement.angle = orbit(ball.arg,ball.mag);
  } else if(centreDelay.hasTimePassedNoUpdate()){
    moveToPos(CENTRE);
  }

  // BOSS LOGIC
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500){
    moveToPos(CENTRE);
  }
}

<<<<<<< HEAD
void Orbit::calcBreakingAttaker(){
  if(ball.exists()){
    rememberTimer.update();
  }
  else if(!rememberTimer.hasTimePassedNoUpdate()){
    ball = prevBall;
  }

  if(ball.exists()){
    centreDelay.update();
    if(iCanShoot){
      if(!iCanShootTimer.hasTimePassedNoUpdate()){
          movement.brake = true;
      } else{
        calcSmallOrbit(); // Moves directly to the ball
      }
    }
    if(ball.arg < SMALL_ORBIT+SMALL_ORBIT_RIGHT || ball.arg > (360-SMALL_ORBIT-SMALL_ORBIT_LEFT)){ // *
      iCanShoot = true;
      if((MAX_SPEED+incrementSpeed)<255){
        incrementSpeed += 0.5;
      }
    }
    else{
      iCanShoot = false;
      iCanShootTimer.update();
      incrementSpeed = 0;
      if((ball.arg < BIG_ORBIT+BIG_ORBIT_RIGHT || ball.arg > (360-BIG_ORBIT-BIG_ORBIT_LEFT))){
        calcBigOrbit(); // Transfers between close orbit and small orbit
        if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
          movement.speed = round(movement.speed * SLOW_SPEED);
        }
      }
      else if(ball.mag < ORBIT_DISTANCE){
        calcCloseOrbit(); // Moves perpendicular to the ball
        // if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
        //   movement.speed = round(movement.speed * (SLOW_SPEED+0.2));
        // }
      }
      else{
        calcTangentOrbit(); // Enters the ball's nearest tangent
        // if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
        //     movement.speed = round(movement.speed * SLOW_SPEED);
        // }
      }
    }
  } else{
    iCanShoot = false;
    iCanShootTimer.update();
    incrementSpeed = 0;
    if(centreDelay.hasTimePassedNoUpdate()){
      moveToPos(CENTRE);
    }
  }
  prevAngle = movement.angle;

  // BOSS LOGIC
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500){
    moveToPos(CENTRE);
  }
}

=======
>>>>>>> parent of c2af799... National Orbit
void Orbit::calcDefender(){ //Assuming PID is good
  if(defendGoal.exists()){
    double hMov;
    Vector moveVector = defendGoal-DEFEND_POSITION;//Movement required go to centre of goal
    double vMov = vGoalie.update(moveVector.j)*1.5;
    if(ball.exists()){
      if(ball.between(345,15) && ball.mag < 550 && defendGoal.j > SURGE_DISTANCE){
<<<<<<< HEAD
        decideOrbit();
        movement.speed = GOALIE_SPEED;
=======
        calcAttacker();
>>>>>>> parent of c2af799... National Orbit
        return;
      }
      else{
        if((defendGoal.i > DEFEND_LEFT_I && ball.arg > 180) || (defendGoal.i < DEFEND_RIGHT_I && ball.arg < 180)){
          hMov = hGoalie.update(ball.arg > 180 ? defendGoal.i-DEFEND_LEFT_I : defendGoal.i-DEFEND_RIGHT_I)*0.3;
          vMov = vGoalie.update(moveVector.j-150)*1.5;
        }
        else{
          hMov = angGoalie.update(ball.arg < 180 ? ball.arg : -(360-ball.arg));
        }
        movement.angle = mod(450-round(toDegrees(atan2(vMov,hMov))),360);
        movement.angle = movement.angle + (movement.angle < 180 ? 25 : -25);
      }
    }
    else{
      hMov = hGoalie.update(moveVector.i);
      movement.angle = mod(450-round(toDegrees(atan2(vMov,hMov))),360);
    }
    movement.speed = constrain(round(goalieSpeed.update(sqrt(hMov*hMov+vMov*vMov))),0,GOALIE_SPEED); // Use the same PID for ball follow and recentre
  }
  else{
<<<<<<< HEAD
    if(ball.exists()){
      decideOrbit();
    }
    else{
      moveToPos(GOALIE_POS);
    }
  }
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500){
    moveToPos(GOALIE_POS);
=======
    // if(ball.exists()){
      // calcAttacker();
    // }
    // else{
      moveToPos(GOALIE_POS);
    // }
>>>>>>> parent of c2af799... National Orbit
  }
}

void Orbit::calcSmallOrbit(){
  movement.speed = SHOOTING_SPEED + incrementSpeed;
  movement.angle = ball.arg < 180 ? ball.arg : -(360-ball.arg);
  // movement.angle = (ball.arg < 180 ? ball.arg*ANGLE_TIGHTENER_RIGHT : 360-(360-ball.arg)*ANGLE_TIGHTENER_LEFT);

  // attackGoal.arg = (attackGoal.arg < 180 ? attackGoal.arg : -(360-attackGoal.arg));
  // ball.arg = (ball.arg < 180 ? ball.arg : -(360-ball.arg));
  // double middleAngle = (attackGoal.arg+ball.arg)/2;
  // movement.angle = middleAngle;
  // Serial.print(attackGoal.arg);
  // Serial.print("\t");
  // Serial.print(ball.arg);
  // Serial.print("\t");
  // Serial.println(movement.angle);
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
  movement.angle = ball.arg + (tangentAngle+10) * (ball.arg < 180 ? 1 : -1);
}

void Orbit::moveToPos(Vector position){
  Vector direction = position - robotPosition;

  double horizontal = horizontalMovement.update(direction.i);
  double vertical = verticalMovement.update(direction.j);
  #if SUPERTEAM
  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -230, 230);
  #else
  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -150, 150);
  #endif
  movement.angle = mod(round(450 - toDegrees(atan2(vertical,horizontal))), 360);
}

void Orbit::manageKicker(){
  if(((role == Role::attack && attackGoal.exists() && attackGoal.between(340,20) && attackGoal.mag < 1100) || role == Role::defend) && hasBall){
    kicker.kick();
  }

}

void Orbit::setBTData(Vector otherBallPos){
  if(!ball.exists()){
    if(otherBallPos.exists()){
      ball = otherBallPos - robotPosition;
    }
  }
}

double Orbit::modelDistance(double distance){
  double val = 1/(1+exp((distance-1250)/250));
  return val;
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
  movement = {-1, 0, 0, false};
}
