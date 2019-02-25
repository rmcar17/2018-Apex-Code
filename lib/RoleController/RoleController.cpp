#include "RoleController.h"

RoleController::RoleController(){

}

void RoleController::update(Vector robot, Vector ball){
  double balli = ball.i;
  double ballj = ball.j;
  myBall = Vector(balli,ballj,0);

  otherBalli = (int)transaction(((uint8_t)0),balli);
  otherBallj = (int)transaction(((uint8_t)1),ballj);
  otherBall = Vector(otherBalli,otherBallj,0);

  Vector toBall = otherBall.operator-(robot);
  ballArg = mod(toDegrees(atan2(toBall.i,toBall.j)),360);
  ballMag = sqrt(pow(toBall.i,2)+pow(toBall.j,2));

  // Serial.print(otherBalli);
  // Serial.print("\t");
  // Serial.println(otherBallj);

  // Serial.print("My: ");
  // Serial.print(balli);
  // Serial.print("\t");
  // Serial.print(ballj);
  // Serial.print("\tOther: ");

  // Serial.print(otherBalli);
  // Serial.print("\t");
  // Serial.println(otherBallj);

  decideRoles();
}

void RoleController::decideRoles(){
  if(!myBall.exists()){
    orbit.setBall(otherBall);
  }
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
