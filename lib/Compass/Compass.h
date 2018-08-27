#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <Common.h>
#include <Debug.h>
#include <Defines.h>

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00

#define COMPASS_CALIBRATION 1.3

class Compass {
  public:
    Compass() {};
    void compassSetup();

    Vector3D readAccelerometer();
    Vector3D readGyroscope();

    void updateAccelerometer();
    void updateGyro();
    void calibrate();

    double getHeading();
  private:
    double heading;
    double zAcc;
    long double calibration = COMPASS_CALIBRATION;

    long previousTime;

    double convertRawAcceleration(int raw) {
        // Since we are using 2G range
        // -2g maps to a raw value of -32768
        // +2g maps to a raw value of 32767

        double a = (raw * 2.0) / 32768.0;
        return a;
    }

    double convertRawGyro(int raw) {
        double g = (raw * 500.0) / 32768.0;
        return g;
    }
};

#endif
