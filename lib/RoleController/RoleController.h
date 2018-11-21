#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include <Arduino.h>
#include <Vector.h>
#include <Pins.h>
#include <Timer.h>
#include <Bluetooth.h>
#include <Orbit.h>
#include <Common.h>

uint16_t transaction(uint8_t command, uint16_t data);

class RoleController {
  public:
    RoleController();
    void update(Vector robot, Vector ball);
    void decideRoles();
    Vector myBall = Vector(0,0);
	Vector otherBall = Vector(0,0);
private:
	int role = ROBOT;
	Timer timer = Timer(1000);
	int otherBalli, otherBallj;
	double ballArg, ballMag;
};

extern Bluetooth bt;
extern Vector vector;
extern Orbit orbit;

#endif
