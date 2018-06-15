#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>
#include <Defines.h>
#include <Vector.h>
#include <Common.h>

class LIDAR {
public:
	LIDAR();
	void setup();
	void update();
	void setComp(int compVal);
	Vector getCoords();
	uint16_t lidarLeft, lidarBack, lidarRight;
private:
	void read();
	void calculateCoords();
	uint8_t sensorData[4];
	Vector coords = Vector(0,0);
	int compAngle = -1;
};


#endif