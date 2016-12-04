#ifndef MPU6050_h
#define MPU6050_h


#define MPU6050_ADDRESS               0x68 // 0x69 when AD0 pin to Vcc
#define MPU6050_REG_GYRO_CONFIG       0x1B // Gyroscope Configuration
#define MPU6050_REG_ACCEL_CONFIG      0x1C // Accelerometer Configuration
#define MPU6050_REG_PWR_MGMT_1        0x6B // Power Management 1

#define MPU6050_REG_ACCEL_XOFFS_H     0x06
#define MPU6050_REG_ACCEL_XOFFS_L     0x07
#define MPU6050_REG_ACCEL_YOFFS_H     0x08
#define MPU6050_REG_ACCEL_YOFFS_L     0x09
#define MPU6050_REG_ACCEL_ZOFFS_H     0x0A
#define MPU6050_REG_ACCEL_ZOFFS_L     0x0B
#define MPU6050_REG_GYRO_XOFFS_H      0x13
#define MPU6050_REG_GYRO_XOFFS_L      0x14
#define MPU6050_REG_GYRO_YOFFS_H      0x15
#define MPU6050_REG_GYRO_YOFFS_L      0x16
#define MPU6050_REG_GYRO_ZOFFS_H      0x17
#define MPU6050_REG_GYRO_ZOFFS_L      0x18

#define MPU6050_REG_ACCEL_XOUT_H      0x3B
#define MPU6050_REG_ACCEL_XOUT_L      0x3C
#define MPU6050_REG_ACCEL_YOUT_H      0x3D
#define MPU6050_REG_ACCEL_YOUT_L      0x3E
#define MPU6050_REG_ACCEL_ZOUT_H      0x3F
#define MPU6050_REG_ACCEL_ZOUT_L      0x40
#define MPU6050_REG_TEMP_OUT_H        0x41
#define MPU6050_REG_TEMP_OUT_L        0x42
#define MPU6050_REG_GYRO_XOUT_H       0x43
#define MPU6050_REG_GYRO_XOUT_L       0x44
#define MPU6050_REG_GYRO_YOUT_H       0x45
#define MPU6050_REG_GYRO_YOUT_L       0x46
#define MPU6050_REG_GYRO_ZOUT_H       0x47
#define MPU6050_REG_GYRO_ZOUT_L       0x48

typedef enum {
    MPU6050_SCALE_2000DPS	= 0b11,
    MPU6050_SCALE_1000DPS	= 0b10,
    MPU6050_SCALE_500DPS	= 0b01,
    MPU6050_SCALE_250DPS	= 0b00
} mpu6050_dps_t;

typedef enum {
    MPU6050_RANGE_16G	= 0b11,
    MPU6050_RANGE_8G	= 0b10,
    MPU6050_RANGE_4G	= 0b01,
    MPU6050_RANGE_2G	= 0b00,
} mpu6050_range_t;


struct vector_t {
    float x;
    float y;
    float z;
};

float dpsPerDigit, rangePerDigit;

#endif