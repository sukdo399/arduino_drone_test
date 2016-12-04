 #include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "quard_copter.h"

#define LOG_MPU6050_INFO
// #define LOG_MPU6050_DATA
    // #define LOG_MPU6050_DATA_ACCELOMETER_LAW
    // #define LOG_MPU6050_DATA_ACCELOMETER_BASE
    // #define LOG_MPU6050_DATA_ACCELOMETER_AXIS
    // #define LOG_MPU6050_DATA_ACCELOMETER_ANGLE
    // #define LOG_MPU6050_DATA_GYRO_LAW
    // #define LOG_MPU6050_DATA_GYRO_BASE
    // #define LOG_MPU6050_DATA_GYRO_AXIS
    // #define LOG_MPU6050_DATA_GYRO_ANGLE
    // #define LOG_MPU6050_DRON_ANGLE
#define LOG_MONITORING
    // #define LOG_MONITORING_LAW
    // #define LOG_MONITORING_AXIS
    // #define LOG_MONITORING_ANGLE
    #define LOG_MONITORING_DRON_ANGLE
    // #define LOG_MONITORING_DRON

void setup() 
{
    // delay(2000);
    Serial.begin(115200);
    initQuardCopter();
}

void loop() 
{
    timer = millis();

    getMPU6050Data();
    #if defined(LOG_MONITORING)
    printMonitoring();
    #endif	

    int diff = delta - (millis() - timer);
    if (diff > 0)
    {
        delay(diff);
    }
    else
    {
        Serial.print("not in time :");
        Serial.println(diff);
    }
}
