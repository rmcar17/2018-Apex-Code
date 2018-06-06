#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>

class LIDAR {
public:
	LIDAR();
	void init();
	void read();
	uint16_t lidarVal[4];
private:
	uint8_t sensorData[4];
};


#endif