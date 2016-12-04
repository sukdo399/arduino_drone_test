#ifndef _QUARD_COPTER_H_
#define _QUARD_COPTER_H_

#include <Wire.h>

#define PIN_LED						13
// uno
/*
#define PIN_MOTOR_1             11
#define PIN_MOTOR_2             3
#define PIN_MOTOR_3             9
#define PIN_MOTOR_4             10
*/

// leonardo
#define PIN_MOTOR_1             6
#define PIN_MOTOR_2             10
#define PIN_MOTOR_3             5
#define PIN_MOTOR_4             9

#define AUTO_CALIBRATE_AMOUNT       300
#define BASE_GRAVITY                9.81
#define COMPLEMENTARY_FILTER_GAIN   0.95

struct vector_t {
    float x; float y; float z;
};
struct motor_power_t {
     int m1; int m2; int m3; int m4;
};
float accelRangePerDigit = .0f, gyroRangePerDigit = .0f;
float rad2degree    = 57.2957;
unsigned long timer = 0;
float delta         = 20;

MPU6050 sensMpu;
motor_power_t motor_power = {0, 0, 0, 0};
int16_t mpu6050raw[6] = {0, 0, 0, 0, 0, 0};
vector_t acelBase = {.0f, .0f, .0f}, gyroBase = {.0f, .0f, .0f};
vector_t acelAxis = {.0f, .0f, .0f}, gyroAxis = {.0f, .0f, .0f};
vector_t acelAngl = {.0f, .0f, .0f}, gyroAngl = {.0f, .0f, .0f};
vector_t angle = {.0f, .0f, .0f};

#endif