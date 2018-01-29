#ifndef I2C_H
#define I2C_H

#include <Wire.h>

void I2Cread(uint8_t address, uint8_t registerAddress, uint8_t nBytes, uint8_t *data);
void I2CwriteByte(uint8_t address, uint8_t registerAddress, uint8_t data);

#endif
