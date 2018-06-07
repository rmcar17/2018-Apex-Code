#include <Lidar.h>

void LIDAR::init(){
	Serial1.begin(115200);
	Serial3.begin(115200);
	Serial2.begin(115200);
	Serial4.begin(115200);

	Serial1.write((uint8_t)0x42);
  Serial1.write((uint8_t)0x57);
  Serial1.write((uint8_t)0x02);
  Serial1.write((uint8_t)0x00);
  Serial1.write((uint8_t)0x00);
  Serial1.write((uint8_t)0x00);
  Serial1.write((uint8_t)0x01);
  Serial1.write((uint8_t)0x06);

  Serial3.write((uint8_t)0x42);
  Serial3.write((uint8_t)0x57);
  Serial3.write((uint8_t)0x02);
  Serial3.write((uint8_t)0x00);
  Serial3.write((uint8_t)0x00);
  Serial3.write((uint8_t)0x00);
  Serial3.write((uint8_t)0x01);
  Serial3.write((uint8_t)0x06);

  Serial2.write((uint8_t)0x42);
  Serial2.write((uint8_t)0x57);
  Serial2.write((uint8_t)0x02);
  Serial2.write((uint8_t)0x00);
  Serial2.write((uint8_t)0x00);
  Serial2.write((uint8_t)0x00);
  Serial2.write((uint8_t)0x01);
  Serial2.write((uint8_t)0x06);

  Serial4.write((uint8_t)0x42);
  Serial4.write((uint8_t)0x57);
  Serial4.write((uint8_t)0x02);
  Serial4.write((uint8_t)0x00);
  Serial4.write((uint8_t)0x00);
  Serial4.write((uint8_t)0x00);
  Serial4.write((uint8_t)0x01);
  Serial4.write((uint8_t)0x06);
}

void LIDAR::read(){
  while(Serial1.available() > 8){
    int sync0 = Serial1.read();
    int sync1 = Serial1.peek();
    if (sync0 == 89 && sync1 == 89){
      Serial1.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial1.read();
      }
      lidarVal[0] = sensorData[1] << 8 | sensorData[0]; 
    }
	}

  while(Serial3.available() > 8){
    int sync0 = Serial3.read();
    int sync1 = Serial3.peek();
    if (sync0 == 89 && sync1 == 89){
      Serial3.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial3.read();
      }
      lidarVal[1] = sensorData[1] << 8 | sensorData[0]; 
    }
  }

  while(Serial2.available() > 8){
    int sync0 = Serial2.read();
    int sync1 = Serial2.peek();
    if (sync0 == 89 && sync1 == 89){
      Serial2.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial2.read();
      }
      lidarVal[2] = sensorData[1] << 8 | sensorData[0]; 
    }
  }

  while(Serial4.available() > 8){
    int sync0 = Serial4.read();
    int sync1 = Serial4.peek();
    if (sync0 == 89 && sync1 == 89){
      Serial4.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial4.read();
      }
      lidarVal[3] = sensorData[1] << 8 | sensorData[0]; 
    }
  }
}