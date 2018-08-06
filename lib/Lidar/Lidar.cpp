#include <Lidar.h>

LIDAR::LIDAR(){

}

void LIDAR::setup(){
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

void LIDAR::update(){
  read();
  calculateCoords();
}

void LIDAR::read(){
  while(Serial1.available() > 8){
    if (Serial1.read() == 89 && Serial1.peek() == 89){
      Serial1.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial1.read();
      }
      lidarValues[0] = (sensorData[1] << 8 | sensorData[0]) * 10;
    }
  }

  while(Serial3.available() > 8){
    if (Serial3.read() == 89 && Serial3.peek() == 89){
      Serial3.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial3.read();
      }
      lidarValues[1] = (sensorData[1] << 8 | sensorData[0]) * 10;
    }
	}


  while(Serial2.available() > 8){
    if (Serial2.read()  == 89 && Serial2.peek() == 89){
      Serial2.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial2.read();
      }
      lidarValues[2] = (sensorData[1] << 8 | sensorData[0]) * 10;
    }
  }

  while(Serial4.available() > 8){
    if (Serial4.read() == 89 && Serial4.peek() == 89){
      Serial4.read();
      for (int i = 0; i < 4; i++){
        sensorData[i] = Serial4.read();
      }
      lidarValues[3] = (sensorData[1] << 8 | sensorData[0]) * 10;
    }
  }

  if(ROBOT==1){
    lidarLeft = lidarValues[1] == 12000 ? 300 : lidarValues[1];
    lidarBack = lidarValues[2] == 12000 ? 300 : lidarValues[2];
    lidarRight = lidarValues[3] == 12000 ? 300 : lidarValues[3];
  } else{
    lidarLeft = lidarValues[0] == 12000 ? 300 : lidarValues[0];
    lidarBack = lidarValues[2] == 12000 ? 300 : lidarValues[2];
    lidarRight = lidarValues[3] == 12000 ? 300 : lidarValues[3];
  }
}

void LIDAR::calculateCoords(){
  double i, j;
  i = ((FIELD_WIDTH-lidarRight*cos(toRadians(compAngle))+lidarLeft)*cos(toRadians(compAngle))/2);
  // i = lidarLeft * cos(toRadians(compAngle));
  j = lidarBack * cos(toRadians(compAngle));
  // Serial.print(lidarLeft);
  // Serial.print("\t");
  // Serial.print(lidarBack);
  // Serial.print("\t");
  // Serial.println(lidarRight);
  coords = Vector(i,j,false);
  // Serial.print(coords.i);
  // Serial.print("\t");
  // Serial.println(coords.j);
}

Vector LIDAR::getCoords(){
  return coords;
}

void LIDAR::setComp(int compVal){
  compAngle = compVal;
}
