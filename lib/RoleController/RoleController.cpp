#include "RoleController.h"

RoleController::RoleController(){

}

void RoleController::update(Vector ball){
  double ballAngle = ball.arg;
  double ballDistance = ball.mag;
  myBall = Vector(ballAngle,ballDistance);
  
  otherBallAngle = (double)transaction(((uint8_t)0),ballAngle);
  otherBallDistance = (double)transaction(((uint8_t)1),ballDistance);
  decideRoles();
}

void RoleController::decideRoles(){
  // if(!vector.exists(myBall)){
  //   Serial.print("I can't see");
  // } else{
  //   Serial.print("I can see");
  // }
  // Serial.print(" and ");
  // if(!vector.exists(otherBall)){
  //   Serial.print("Other can't see");
  // } else{
  //   Serial.print("Other can see");
  // }
  // Serial.println();

  /*
  Pseudocode
  Things to consider (by priority):
  - angle to ball (infront or behind)
  - distance to ball
  - robot's current role
  - last update time (wait for a time period till you can change again)

  How to achieve this?
  Have a "master" robot and a "slave" robot
  Only master robot controls role handling, although, calculations
  begin from the striker robot's perspecive.
  If other team robot is removed, prioritise defence.

  Initially:
  Set master to attack and slave to defence

  Once Data is received:
  - Note: aRobot is attacking and dRobot is defending
  | aRobot & dRobot angle are both forward,
    - set closest robot to attack

  */
}
