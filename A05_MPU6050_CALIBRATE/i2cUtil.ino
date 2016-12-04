#include "i2cUtil.h"

uint8_t swap;
#define SWAP(x,y) swap = x; x = y; y = swap

int8_t i2cRead(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) 
{
    int8_t count = 0, error = 0, n = 0;
    uint32_t t1 = millis();

    Wire.beginTransmission(devAddr);
    n = Wire.write(regAddr);
    if (n != 1) return (-10);

    error = Wire.endTransmission(false);	// hold the I2C-bus
    if (error != 0) return (error);

    // Third parameter is true: release I2C-bus after data is read
    Wire.requestFrom(devAddr, length);
    while(Wire.available() && (count < length || millis() - t1 < I2C_READ_TIMEOUT)){
        data[count++] = Wire.read();
    }
    if (count != length) return (-11);

    return(error);	// return : no error
}

int8_t i2cWrite(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) 
{
    int n = 0, error = 0;

    Wire.beginTransmission(devAddr);
    n = Wire.write(regAddr);		// write the start address
    if (n != 1) return (-20);

    n = Wire.write(data, length);	// write data bytes
    if (n != 1) return (-21);

    error = Wire.endTransmission(true);	// release the I2C-bus
    if (error != length) return (error);

    return (error);	// return : no error
}

bool i2cReadBit(uint8_t devAddr, uint8_t regAddr, uint8_t pos) 
{
    uint8_t value;

    i2cRead(devAddr, regAddr, 1, &value);
    return ((value >> pos) & 1);
}

void i2cWriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t pos, bool state) 
{
    uint8_t value;

    i2cRead(devAddr, regAddr, 1, &value);
    if (state) value |= (1 << pos);
    else value &= ~(1 << pos);

    i2cWrite(devAddr, regAddr, 1, &value);
}
