#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <Common.h>
#include <Debug.h>
#include <Defines.h>

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

#define COMPASS_CALIBRATION 1.39
#define COMPASS_CALIBRATION_TIME 1000

class Compass {
public:
    double heading;
    double calibration = COMPASS_CALIBRATION;

    Compass() {};
    void compassSetup();

    Vector3D readAccelerometer();
    Vector3D readGyroscope();
    Vector3D readMagnetometer();

    void updateGyro();
    double calibrate();

private:
    long previousTime;

    double convertRawAcceleration(int raw){
        // Since we are using 2G range
        // -2g maps to a raw value of -32768
        // +2g maps to a raw value of 32767

        double a = (raw * 2.0) / 32768.0;
        return a;
    }

    double convertRawGyro(int raw) {
        // Since we are using 500 degrees/seconds range
        // -500 maps to a raw value of -32768
        // +500 maps to a raw value of 32767

        double g = (raw * 500.0) / 32768.0;
        return g;
    }
};

// extern Compass compass;

#endif