#include "Orbit.h"

Orbit::Orbit(){

}

void Orbit::setRole(PlayMode playMode){
  role = playMode;
}

void Orbit::setBallData(BallData ballData){
  ball = ballData;
}

void Orbit::setGoalData(GoalData goalData){
  goal = goalData;
}

void Orbit::setCompAngle(int heading){
  compAngle = heading;
}

MoveData Orbit::getMoveData(){
  return movement;
}

void Orbit::calculateMoveData(){
  if(role == PlayMode::attacker){
    calcAttacker();
  }
  else{
    calcDefender();
  }
  #if DEBUG_ORBIT
    Serial.print("BALL ANGLE: ");
    Serial.print(ball.angle);
    Serial.print("  MOVE ANGLE: ");
    Serial.println(movement.angle);
  #endif
}

void Orbit::calculateRotation(){
  double rotate;

  if(goal.visible){
    if(role == PlayMode::attacker){
    rotate = rotation.update(goal.angle < 180 ? goal.angle : -(360 - goal.angle));
    }
    else{
      double oppositeAngle = mod(goal.angle + 180, 360);
      rotate = rotation.update(oppositeAngle < 180 ? oppositeAngle : -(360 - oppositeAngle));
    }
  }
  else{
    rotate = rotation.update(compAngle < 180 ? compAngle : -(360 - compAngle));
  }

  movement.rotation = round(rotate);
}

void Orbit::calcAttacker(){
  if(ball.visible){
    if(ball.distance > FAR_ORBIT){
      if(isAngleBetween(ball.angle, 360 - SMALL_ORBIT, SMALL_ORBIT)){
        calcSmallOrbit();
      }
      else if(isAngleBetween(ball.angle, 360 - BIG_ORBIT, BIG_ORBIT)){
        calcBigOrbit();
      }
      else if(ball.distance > CLOSE_ORBIT){
        calcCloseOrbit();
      }
      else if(ball.distance > FAR_ORBIT){
        calcMediumOrbit();
      }
    }
    else{
      calcFarOrbit();
    }
  }
  else{
    if(goal.visible){
      centre();
    }
    //If can't see goal or ball, the robot
    //can't do anything so just compass correct
  }
}

void Orbit::calcDefender(){
  if(ball.visible){
    if(goal.visible){
      if(isAngleBetween(ball.angle, 270, 90)){
        moveToBall();
      }
      else{
        //Orbit around the ball normally
        calcAttacker();
      }
    }
    else {

    }
  }
  else{
    if(goal.visible){
      centre();
    }
    //If can't see goal or ball, the robot
    //can't do anything so just compass correct
  }
}

void Orbit::calcSmallOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = round(ball.angle < 180 ? ball.angle * ORBIT_FORWARD_ANGLE_TIGHTENER : 360 - (360 - ball.angle) * ORBIT_FORWARD_ANGLE_TIGHTENER);
}

void Orbit::calcBigOrbit(){
  double closeness, angleBuffer;
  int finalAngle;

  if(ball.angle < 180){
    closeness = (double) (ball.angle - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = round(ball.angle * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + ball.angle * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness);
  }
  else{
    closeness = (double) ((360 - ball.angle) - SMALL_ORBIT) / (double) (BIG_ORBIT - SMALL_ORBIT);
    angleBuffer = closeness * 90;
    finalAngle = mod(round(360 - ((360 - ball.angle) * ORBIT_FORWARD_ANGLE_TIGHTENER + angleBuffer + (360 - ball.angle) * (1 - ORBIT_FORWARD_ANGLE_TIGHTENER) * closeness)), 360);
  }

  movement.speed = MAX_SPEED;
  movement.angle = finalAngle;
}

void Orbit::calcCloseOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.angle < 180 ? ball.angle + 90 : ball.angle - 90;
}

void Orbit::calcMediumOrbit(){
  double closeness = (double) (ball.distance - FAR_ORBIT) / (double) (CLOSE_ORBIT - FAR_ORBIT);
  int angleBuffer = round(closeness * 90);

  movement.speed = MAX_SPEED;
  movement.angle = ball.angle + (ball.angle < 180 ? angleBuffer : -angleBuffer);
}

void Orbit::calcFarOrbit(){
  movement.speed = MAX_SPEED;
  movement.angle = ball.angle;
}

void Orbit::centre(){
  double goalAngle = toRadians(compAngle + goal.angle);

  double correctedVerticalDistance = goal.distance * cos(goalAngle) + (role == PlayMode::attacker ? -CENTRE_ATTACKER_DISTANCE : CENTRE_DEFENDER_DISTANCE);
  double correctedHorizontalDistance = goal.distance * sin(goalAngle);

  movement.speed = MAX_SPEED;
  movement.angle = mod(round(toDegrees(atan2(correctedVerticalDistance,correctedHorizontalDistance)))-compAngle,360);
}

void Orbit::moveToBall(){
  //Won't work when comparing
  //TSOPs to camera
  double correctedVerticalDistance = goal.distance * cos(toRadians(compAngle + goal.angle)) + CENTRE_DEFENDER_DISTANCE;
  double correctedHorizontalDistance = isAngleBetween(ball.angle, 360 - DEFEND_SMALL_ANGLE, DEFEND_SMALL_ANGLE) ? 0 : ball.distance * sin((double)toRadians(ball.angle + compAngle));

  movement.speed = MAX_SPEED;
  movement.angle = mod(round(toDegrees(atan2(correctedVerticalDistance,correctedHorizontalDistance)))-compAngle,360);
}

void Orbit::resetAllData(){
  role = PlayMode::undecided;
  ball = {-1, 0, false};
  goal = {-1, 0, false};
  movement = {-1, 0, 0};
  compAngle = 0;
}
