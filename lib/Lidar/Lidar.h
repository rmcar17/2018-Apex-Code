#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>

class Lidar {
public:
	Lidar();

	void setup(HardwareSerial serialPort);
	void read();
	int getDistance();
private:
	int lidarVal;
	HardwareSerial serialPin;
};


#endif
