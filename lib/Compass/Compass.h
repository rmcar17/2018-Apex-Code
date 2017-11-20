#ifndef COMPASS_H_
#define COMPASS_H_

#include <I2C.h>
#include <Defines.h>
#include <Common.h>

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_500_DPS 0x08

#define ACC_FULL_SCALE_2_G 0x00

#define COMPASS_CALIBRATION 1.3

class Compass {
public:
    double heading;
    long double calibration = COMPASS_CALIBRATION;

    Compass() {};
    void compassSetup();

    Vector3D readGyroscope();

    void updateGyro();
    void calibrate();

private:
    long previousTime;

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
