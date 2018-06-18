#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include <Vector.h>
#include <Pins.h>
#include <Timer.h>
#include <Bluetooth.h>

uint16_t transaction(uint8_t command, uint16_t data);

class RoleController {
  public:
    RoleController();
    void update(Vector ball);
    void decideRoles();
private:
	int role = ROBOT;
	Vector myBall = Vector(0,0);
	Vector otherBall = Vector(0,0);
	Timer timer = Timer(1000);
	double otherBallAngle, otherBallDistance;
};

extern Bluetooth bt;
extern Vector vector;

#endif
