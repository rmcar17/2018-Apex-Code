#include "I2C.h"

void I2Cread(uint8_t address, uint8_t registerAddress, uint8_t nBytes, uint8_t *data) {
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.endTransmission();

    Wire.requestFrom(address, nBytes);
    uint8_t index = 0;
    while (Wire.available()) {
        data[index] = Wire.read();
        index++;
    }
}

void I2CwriteByte(uint8_t address, uint8_t registerAddress, uint8_t data) {
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(data);
    Wire.endTransmission();
}
