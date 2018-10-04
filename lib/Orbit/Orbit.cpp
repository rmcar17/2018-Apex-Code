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
  if(ball.exists()){
    rememberTimer.update();
  }
  else if(!rememberTimer.hasTimePassedNoUpdate()){
    ball = prevBall;
  }
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
    if(angle == -1 || angle == 65506){
        return 65506;
    }
    /* Simple orbit from last year for testing */
    if(ratio < 0.00 || ratio > 1.00){
        ratio = 1.00;
    }
    if(angle == -1){
        return -1.00;
    }else if(angle < 30 || angle > 330){
        movement.speed = MAX_SPEED;
        return angle < 180 ? (angle + (angle * 1.1 * ratio)) : (angle - ((360 - angle) * 1.1 * ratio));
    }else{
        return angle < 180 ? (angle + (90 * ratio)) : (angle - (90 * ratio));
    }
}

double Orbit::orbit(int angle, int distance){
    /* Ensure that we actually have a distance */
    if(angle == -1 || angle == 65506){
        return 65506;
    }
    if(distance != 0){
        if(distance > 600){
            /* Move ball direction */
            return angle;
        }else if(distance > 400 && distance <= 600){
            /* A lil bit closer */
            return orbitSimple(angle, 0.2);
        }else if(distance > 230 && distance <= 400){
            /* Almost Normal Orbit orbit */
            return orbitSimple(angle, 0.23);
        }else if(distance <= 230){
            /* More Aggressive than Normal Orbit */
            return orbitSimple(angle, 0.4);
        }
    }else{ /* Do Normal Orbit */
        return orbitSimple(angle, 0.6);
    }
}

void Orbit::calcAttacker(){
  if(ball.exists()){
    rememberTimer.update();
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
  }
  
  // BOSS LOGIC
  if((lidars.lidarLeft+lidars.lidarRight)/2 < 500){
    moveToPos(CENTRE);
  }

  // if(ball.exists()){
  //   centreDelay.update();
  //   if(iCanShoot){
  //     if(!iCanShootTimer.hasTimePassedNoUpdate()){
  //         movement.brake = true;
  //     } else{
  //       calcSmallOrbit(); // Moves directly to the ball
  //     }
  //   }
  //   if(ball.arg < SMALL_ORBIT+SMALL_ORBIT_RIGHT || ball.arg > (360-SMALL_ORBIT-SMALL_ORBIT_LEFT)){ // *
  //     iCanShoot = true;
  //     if((MAX_SPEED+incrementSpeed)<255){
  //       incrementSpeed += 0.5;
  //     }      
  //   }
  //   else{
  //     iCanShoot = false;
  //     iCanShootTimer.update();
  //     incrementSpeed = 0;
  //     if((ball.arg < BIG_ORBIT+BIG_ORBIT_RIGHT || ball.arg > (360-BIG_ORBIT-BIG_ORBIT_LEFT))){
  //       calcBigOrbit(); // Transfers between close orbit and small orbit
  //       if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
  //         movement.speed = round(movement.speed * SLOW_SPEED);
  //       }
  //     }
  //     else if(ball.mag < ORBIT_DISTANCE){
  //       calcCloseOrbit(); // Moves perpendicular to the ball
  //       if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
  //         movement.speed = round(movement.speed * (SLOW_SPEED+0.2));
  //       }
  //     }
  //     else{
  //       calcTangentOrbit(); // Enters the ball's nearest tangent
  //       if((ball.arg < SLOW_ANGLE || ball.arg > (360-SLOW_ANGLE))&&ball.mag < SLOW_DISTANCE){
  //           movement.speed = round(movement.speed * SLOW_SPEED);
  //       }
  //     }
  //   }
  // } else{
  //   iCanShoot = false;
  //   iCanShootTimer.update();
  //   incrementSpeed = 0;
  //   if(centreDelay.hasTimePassedNoUpdate()){
  //     moveToPos(CENTRE);
  //   }
  // }
  // prevAngle = movement.angle;
}

void Orbit::calcDefender(){ //Assuming PID is good
  if(defendGoal.exists()){
    double hMov;
    Vector moveVector = defendGoal-DEFEND_POSITION;//Movement required go to centre of goal
    double vMov = vGoalie.update(moveVector.j)*1.5;
    if(ball.exists()){
      if(ball.between(340,20) && ball.mag < 500 && defendGoal.j > SURGE_DISTANCE){
        calcAttacker();
        return;
      }
      else{
        if((defendGoal.i > DEFEND_LEFT_I && ball.arg > 180) || (defendGoal.i < DEFEND_RIGHT_I && ball.arg < 180)){
          hMov = hGoalie.update(ball.arg > 180 ? defendGoal.i-DEFEND_LEFT_I : defendGoal.i-DEFEND_RIGHT_I);
        }
        else{
          hMov = angGoalie.update(ball.arg < 180 ? ball.arg : -(360-ball.arg));
        }
        movement.angle = mod(450-round(toDegrees(atan2(vMov,hMov))),360);
        movement.angle = movement.angle + (movement.angle < 180 ? 15 : -15);
      }
    }
    else{
      hMov = hGoalie.update(moveVector.i);
      movement.angle = mod(450-round(toDegrees(atan2(vMov,hMov))),360);
    }
    movement.speed = constrain(round(goalieSpeed.update(sqrt(hMov*hMov+vMov*vMov))),0,MAX_SPEED); // Use the same PID for ball follow and recentre
  }
  else{
    // if(ball.exists()){
    //   calcAttacker();
    // }
    // else{
      moveToPos(CENTRE);
    // }
  }
}

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED + incrementSpeed;
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
  movement.speed = constrain(round(sqrt(horizontal * horizontal + vertical * vertical)), -MAX_SPEED, MAX_SPEED);
  #endif
  movement.angle = mod(round(450 - toDegrees(atan2(vertical,horizontal))), 360);
}

void Orbit::manageKicker(){
  if(hasBall){
    kicker.kick();
  }
}

void Orbit::manageBluetooth(){
  bt.receive();

  int btSendData[BT_DATA_SIZE] = {round(ballPosition.i), round(ballPosition.j), round(robotPosition.i), round(robotPosition.j)};
  bt.send(&btSendData[0]);

  if(!ball.exists()){
    ball = bt.getOtherBallPos() - robotPosition;
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
