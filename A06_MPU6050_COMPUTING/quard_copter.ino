#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "quard_copter.h"

void initQuardCopter() 
{
    pinMode(PIN_MOTOR_1, OUTPUT);
    pinMode(PIN_MOTOR_2, OUTPUT);
    pinMode(PIN_MOTOR_3, OUTPUT);
    pinMode(PIN_MOTOR_4, OUTPUT);

    initMPU6050();
}

void initMPU6050() 
{
    sensMpu.reset();
    delay(300);
    sensMpu.setSleepEnabled(false);
    sensMpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);	//250, 500, 1000, 2000
    sensMpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);	//2, 4, 8, 16
    accelRangePerDigit = sensMpu.getAccelRangePerDigit();
    gyroRangePerDigit  = sensMpu.getGyroRangePerDigit();
    // digital low pass filter (HW), delay time....19ms
    // sensMpu.setDLPFMode(6);
    // sensMpu.setDHPFMode(4);

    #if defined(LOG_MPU6050_INFO)
    printMpu6050Status();
    #endif

    autoCalibrateMPU6050();
}

void autoCalibrateMPU6050() 
{
    // Serial.println("Calibrating MPU6050. Don't move the hardware...............");

    setMotorPower(20, false);
    for(int i=0; i<AUTO_CALIBRATE_AMOUNT; i++)
    {
        sensMpu.getMotion6(mpu6050raw, mpu6050raw+1, mpu6050raw+2, mpu6050raw+3, mpu6050raw+4, mpu6050raw+5);
        acelBase.x = ((acelBase.x * i) + (float)mpu6050raw[0]) / (float)(i+1);
        acelBase.y = ((acelBase.y * i) + (float)mpu6050raw[1]) / (float)(i+1);
        acelBase.z = ((acelBase.z * i) + (float)mpu6050raw[2]) / (float)(i+1);
        gyroBase.x = ((gyroBase.x * i) + (float)mpu6050raw[3]) / (float)(i+1);
        gyroBase.y = ((gyroBase.y * i) + (float)mpu6050raw[4]) / (float)(i+1);
        gyroBase.z = ((gyroBase.z * i) + (float)mpu6050raw[5]) / (float)(i+1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MPU6050 Function
void getMPU6050Data() 
{
    sensMpu.getMotion6(mpu6050raw, mpu6050raw+1, mpu6050raw+2, mpu6050raw+3, mpu6050raw+4, mpu6050raw+5);

    acelAxis.x = (mpu6050raw[0] - acelBase.x) * accelRangePerDigit;
    acelAxis.y = (mpu6050raw[1] - acelBase.y) * accelRangePerDigit;
    acelAxis.z = (mpu6050raw[2] - acelBase.z) * accelRangePerDigit + 1;
    gyroAxis.x = (mpu6050raw[3] - gyroBase.x) * gyroRangePerDigit;
    gyroAxis.y = (mpu6050raw[4] - gyroBase.y) * gyroRangePerDigit;
    gyroAxis.z = (mpu6050raw[5] - gyroBase.z) * gyroRangePerDigit;


    acelAngl.x = atan2( acelAxis.y, sqrt(pow(acelAxis.x,2) + pow(acelAxis.z,2)) ) * rad2degree;
    acelAngl.y = atan2(-acelAxis.x, sqrt(pow(acelAxis.y,2) + pow(acelAxis.z,2)) ) * rad2degree;
    // z축은 자기장과 같이 고려애햐함.
    acelAngl.z = atan2( acelAxis.z, sqrt(pow(acelAxis.x,2) + pow(acelAxis.y,2)) ) * rad2degree;
    gyroAngl.x = (gyroAxis.x / 1000 * delta) + angle.x;
    gyroAngl.y = (gyroAxis.y / 1000 * delta) + angle.y;
    gyroAngl.z = (gyroAxis.z / 1000 * delta) + angle.z;

    // 상보필터 적용.
    angle.x = (gyroAngl.x * COMPLEMENTARY_FILTER_GAIN) + (acelAngl.x * (1-COMPLEMENTARY_FILTER_GAIN));
    angle.y = (gyroAngl.y * COMPLEMENTARY_FILTER_GAIN) + (acelAngl.y * (1-COMPLEMENTARY_FILTER_GAIN));
    angle.z = gyroAngl.z;

    #if defined(LOG_MPU6050_DATA)
    printMpu6050Data();
    #endif    	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR Function
void setMotorPower() 
{
    analogWrite(PIN_MOTOR_1, motor_power.m1); analogWrite(PIN_MOTOR_4, motor_power.m4);
    analogWrite(PIN_MOTOR_3, motor_power.m3); analogWrite(PIN_MOTOR_2, motor_power.m2);

    #if defined(LOG_MOTOR_INFO)
    printMotorPower();
    #endif
}

void setMotorPower(int m1, int m2, int m3, int m4, boolean isDelta) 
{
    if (isDelta) 
    {
    	motor_power.m1 += m1; motor_power.m2 += m2; motor_power.m3 += m3; motor_power.m4 += m4;
    } 
    else 
    {
    	motor_power.m1 = m1; motor_power.m2 = m2; motor_power.m3 = m3; motor_power.m4 = m4;
    }
    setMotorPower();
}

void setMotorPower(int power, boolean isDelta) 
{
    setMotorPower(power, power, power, power, isDelta);
}
