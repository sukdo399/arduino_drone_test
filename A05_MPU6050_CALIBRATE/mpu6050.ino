#include "i2cUtil.h"
#include "mpu6050.h"

void setGyroScale(mpu6050_dps_t gyroScale)
{
    uint8_t value;

    switch (gyroScale) 
    {
        case MPU6050_SCALE_250DPS:	dpsPerDigit = .007633f; break;
        case MPU6050_SCALE_500DPS:	dpsPerDigit = .015267f; break;
        case MPU6050_SCALE_1000DPS:	dpsPerDigit = .030487f; break;
        case MPU6050_SCALE_2000DPS:	dpsPerDigit = .060975f;	break;
        default: break;
    }

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_GYRO_CONFIG, 1, &value);
    value &= 0b11100111;
    value |= (gyroScale << 3);
    i2cWrite(MPU6050_ADDRESS, MPU6050_REG_GYRO_CONFIG, 1, &value);
}

void setAccelRange(mpu6050_range_t accelRange) 
{
    uint8_t value;

    switch (accelRange) 
    {
        case MPU6050_RANGE_2G:	rangePerDigit = .00006f; break;
        case MPU6050_RANGE_4G:	rangePerDigit = .00012f; break;
        case MPU6050_RANGE_8G:	rangePerDigit = .00024f; break;
        case MPU6050_RANGE_16G:	rangePerDigit = .00049f; break;
        default: break;
    }	

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_ACCEL_CONFIG, 1, &value);
    value &= 0b11100111;
    value |= (accelRange << 3);
    i2cWrite(MPU6050_ADDRESS, MPU6050_REG_ACCEL_CONFIG, 1, &value);
}

uint8_t mpu6050ReadRegWord(uint8_t regAddr, int16_t *data) 
{
    int8_t error = 0;
    uint8_t* value = (uint8_t *)data;

    error = i2cRead(MPU6050_ADDRESS, regAddr, 2, value);
    if (error != 0) return (error);
    SWAP(value[0], value[1]);
}

bool mpu6050GetSleepMode() 
{
    return i2cReadBit(MPU6050_ADDRESS, MPU6050_REG_PWR_MGMT_1, 6);
}

bool mpu6050SetSleepMode(bool state) 
{
    i2cWriteBit(MPU6050_ADDRESS, MPU6050_REG_PWR_MGMT_1, 6, state);
}

bool mpu6050Reset() 
{
    i2cWriteBit(MPU6050_ADDRESS, MPU6050_REG_PWR_MGMT_1, 7, true);
    delay(200); /// Waiting for the reset to complete
    i2cWriteBit(MPU6050_ADDRESS, MPU6050_REG_PWR_MGMT_1, 7, false);
}

mpu6050_range_t mpu6050GetAccelRange() 
{
    uint8_t value;
    i2cRead(MPU6050_ADDRESS, MPU6050_REG_ACCEL_CONFIG, 1, &value);
    value &= 0b00011000;
    value >>= 3;
    return (mpu6050_range_t)value;
}

vector_t mpu6050GetAccelOffset() 
{
    uint8_t temp[6] = {0, 0, 0, 0, 0, 0};
    vector_t value = {.0f, .0f, .0f};

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_ACCEL_XOFFS_H, 6, temp);
    value.x = temp[0] << 8 | temp[1];
    value.y = temp[2] << 8 | temp[3];
    value.z = temp[4] << 8 | temp[5];

    return value;
}

mpu6050_range_t mpu6050GetGyroScale() 
{
    uint8_t value;
    i2cRead(MPU6050_ADDRESS, MPU6050_REG_GYRO_CONFIG, 1, &value);
    value &= 0b00011000;
    value >>= 3;
    return (mpu6050_range_t)value;
}

vector_t mpu6050GetGyroOffset() 
{
    uint8_t temp[6] = {0, 0, 0, 0, 0, 0};
    vector_t value = {.0f, .0f, .0f};

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_GYRO_XOFFS_H, 6, temp);
    value.x = temp[0] << 8 | temp[1];
    value.y = temp[2] << 8 | temp[3];
    value.z = temp[4] << 8 | temp[5];

    return value;
}

///////////////////////////////////////////////////////////////////////////////
// 센서 데이터 가져오기
int16_t readRawTemperature() 
{
    int16_t value;
    mpu6050ReadRegWord(MPU6050_REG_TEMP_OUT_H, &value);
    return value;
}

float readTemperature() 
{
    int16_t T = readRawTemperature();

    return (float) T / 325 + 35;
}

vector_t mpu6050RawAccel() 
{
    uint8_t temp[6] = {0, 0, 0, 0, 0, 0};
    vector_t value = {.0f, .0f, .0f};

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_ACCEL_XOUT_H, 6, temp);
    value.x = temp[0] << 8 | temp[1];
    value.y = temp[2] << 8 | temp[3];
    value.z = temp[4] << 8 | temp[5];

    return value;
}

vector_t mpu6050Accel() 
{
    vector_t value = {.0f, .0f, .0f};
    vector_t raw = mpu6050RawAccel();

    value.x = raw.x * rangePerDigit;
    value.y = raw.y * rangePerDigit;
    value.z = raw.z * rangePerDigit;

    return value;
}

vector_t mpu6050RawGyro() 
{
    uint8_t temp[6] = {0, 0, 0, 0, 0, 0};
    vector_t value = {.0f, .0f, .0f};

    i2cRead(MPU6050_ADDRESS, MPU6050_REG_GYRO_XOUT_H, 6, temp);
    value.x = temp[0] << 8 | temp[1];
    value.y = temp[2] << 8 | temp[3];
    value.z = temp[4] << 8 | temp[5];

    return value;
}

vector_t mpu6050Gyro() 
{
    vector_t value = {.0f, .0f, .0f};
    vector_t raw = mpu6050RawGyro();

    value.x = raw.x * dpsPerDigit;
    value.y = raw.y * dpsPerDigit;
    value.z = raw.z * dpsPerDigit;

    return value;
}

///////////////////////////////////////////////////////////////////////////////
// 센서 설정값 로깅
void mpu6050PrintStatus() 
{
    Serial.println("::::: checking MPU6050 sensor :::::");
    Serial.print(" > Sleep Mode : ");
    Serial.println(mpu6050GetSleepMode() ? "Enabled" : "Disabled");
    Serial.print(" > Accelerometer Range : ");
    switch(mpu6050GetAccelRange()) 
    {
        case MPU6050_RANGE_16G:	Serial.println("+/- 16g"); break;
        case MPU6050_RANGE_8G:	Serial.println("+/- 8g"); break;
        case MPU6050_RANGE_4G:	Serial.println("+/- 4g"); break;
        case MPU6050_RANGE_2G:	Serial.println("+/- 2g"); break;
    }
    Serial.print(" > Gyroscope Scale     : ");
    switch(mpu6050GetGyroScale()) 
    {
        case MPU6050_SCALE_2000DPS:	Serial.println("2000 dps"); break;
        case MPU6050_SCALE_1000DPS:	Serial.println("1000 dps"); break;
        case MPU6050_SCALE_500DPS:	Serial.println("500 dps"); break;
        case MPU6050_SCALE_250DPS:	Serial.println("250 dps"); break;
    }

    vector_t accelOffset = mpu6050GetAccelOffset();
    Serial.print(" > Accelerometer offsets [x:");
    Serial.print(accelOffset.x);
    Serial.print(", y:");
    Serial.print(accelOffset.y);
    Serial.print(", z:");
    Serial.print(accelOffset.z);
    Serial.println("]");

    vector_t gyroOffset = mpu6050GetGyroOffset();
    Serial.print(" > Gyroscope offsets     [x:");
    Serial.print(gyroOffset.x);
    Serial.print(", y:");
    Serial.print(gyroOffset.y);
    Serial.print(", z:");
    Serial.print(gyroOffset.z);
    Serial.println("]");

    Serial.println();	
}