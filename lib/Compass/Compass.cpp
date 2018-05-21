#include "Compass.h"

void Compass::compassSetup() {
    I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);

    previousTime = micros();
};
Vector3D Compass::readGyroscope() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);

    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];

    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}

void Compass::updateGyro() {
  double reading = (double) readGyroscope().z;

	long currentTime = micros();
  heading += (((double)(currentTime - previousTime) / 1000000.0) * (reading - calibration));
	heading = doubleMod(heading, 360.0);

	previousTime = currentTime;

  #if DEBUG_COMPASS
    Serial.print("HEADING: ");
    Serial.println(heading,5);
  #endif
}

double Compass::getHeading(){
  return heading;
}

void Compass::calibrate() {
  calibration = 0;
  for(int cal=0;cal<IMU_CALIBRATION_COUNT;cal++){
    calibration += readGyroscope().z;
  }
  calibration = calibration/IMU_CALIBRATION_COUNT;
}
