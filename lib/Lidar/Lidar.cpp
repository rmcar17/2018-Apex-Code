#include <Lidar.h>

Lidar::Lidar(){

}

void Lidar::setup(HardwareSerial serialPort){
	serialPin = serialPort;
	serialPin.begin(115200);

	serialPin.write((uint8_t)0x42);
	serialPin.write((uint8_t)0x57);
	serialPin.write((uint8_t)0x02);
	serialPin.write((uint8_t)0x00);
	serialPin.write((uint8_t)0x00);
	serialPin.write((uint8_t)0x00);
	serialPin.write((uint8_t)0x01);
	serialPin.write((uint8_t)0x06);
}

void Lidar::read(){
	int sensorData[4] = {0};
	while(serialPin.available() > 8){
    	if(serialPin.read() == 89 && serialPin.peek() == 89){
	      	serialPin.read();
	      	for (int i = 0; i < 4; i++){
	        	sensorData[i] = serialPin.read();
	      	}
	    	lidarVal = sensorData[1] << 8 | sensorData[0];
	    }
  	}
}

int Lidar::getDistance(){
	return lidarVal * 10; // To convert cm to mm
}
