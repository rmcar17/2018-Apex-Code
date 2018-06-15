#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>
#include <Defines.h>
#include <Vector.h>

class LIDAR {
public:
	LIDAR();
	void setup();
	void update();
	Vector getCoords();
	uint16_t lidarLeft, lidarBack, lidarRight;
private:
	void read();
	void calculateCoords();
	uint8_t sensorData[4];
	Vector coords = Vector(0,0);
};


#endif