#include "RoleController.h"

RoleController::RoleController(){

}

void RoleController::decideRoles(){
  /*
  Pseudocode
  Things to consider (by priority):
  - angle to ball
  - distance to ball
  - robot's position
  - robot's current role
  - last update time

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
