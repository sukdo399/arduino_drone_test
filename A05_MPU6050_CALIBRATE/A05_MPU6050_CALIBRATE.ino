#include <Arduino.h>
#include "i2cUtil.h"
#include "mpu6050.h"

// uno
/*
#define PIN_MOTOR_1				11
#define PIN_MOTOR_2				3
#define PIN_MOTOR_3				9
#define PIN_MOTOR_4				10
*/

// leonardo
#define PIN_MOTOR_1             6
#define PIN_MOTOR_2             10
#define PIN_MOTOR_3             5
#define PIN_MOTOR_4             9

float rad2degree = 57.2957;
float delta      = 20;
// float delta      = 2000;
unsigned long t  = 0;

vector_t accelAngel, gyroAngel, gyroBase;

void setup() 
{
    // Serial.begin(19200);
    Serial.begin(115200);

    mpu6050Reset();
    setAccelRange(MPU6050_RANGE_4G);
    setGyroScale(MPU6050_SCALE_250DPS);
    mpu6050SetSleepMode(false);
    mpu6050PrintStatus();

    // we need initial value for integral.
    gyroBase = mpu6050Gyro();
    pinMode(PIN_MOTOR_1, OUTPUT);
    pinMode(PIN_MOTOR_2, OUTPUT);
    pinMode(PIN_MOTOR_3, OUTPUT);
    pinMode(PIN_MOTOR_4, OUTPUT);	
}

void loop() 
{
    t = millis();
    printTemperature();
    printAccelerometer();
    printGyroscope();
    // setMotorPower(20);

    // Serial.println(((float)(millis()-t)/delta)*100);
    // Making sure the cycle time is equal to delta    
    while((millis()-t) < delta)
    {
        ;
    }
}

void printTemperature() 
{
    float temp = readTemperature();
    Serial.print("Temperature RAW[");
    Serial.print(readRawTemperature());
    Serial.print("] ºC[");
    Serial.print(readTemperature());
    Serial.println("]");
}

// 가만히 떠 있으면 정확하지만
// 같은 각도 상태에서 움직인다고 생각해보면...?
// 상보 필터 필요.
void printAccelerometer() 
{
	// vector_t rawAccelValue = mpu6050RawAccel();
    vector_t accelValue    = mpu6050Accel();

    accelAngel.x = atan2(accelValue.y, accelValue.z) * rad2degree;
    accelAngel.y = atan2(accelValue.x, accelValue.z) * rad2degree;
    // z축은 자기장 센서와 같이 계산 해야함.
    accelAngel.z = atan2(accelValue.z, sqrt(accelValue.x*accelValue.x + accelValue.y*accelValue.y)) * rad2degree;

    Serial.print("Accelerometer VALUE[x:");
    Serial.print(accelValue.x);
    Serial.print(", y:");
    Serial.print(accelValue.y);
    Serial.print(", z:");
    Serial.print(accelValue.z);
    Serial.print("] AXIS ANGLE[x:");
    Serial.print(accelAngel.x);
    Serial.print(", y:");
    Serial.print(accelAngel.y);
    Serial.print(", z:");
    Serial.print(accelAngel.z);
    Serial.println("]");
}

// integral
// 각속도기 때문에 멈추면 다시 0으로 가니까.
// 오차가 누적됨.
void printGyroscope() 
{
    vector_t gyroDiffBase;
    // vector_t rawGyroValue = mpu6050RawGyro();
    vector_t gyroValue    = mpu6050Gyro();

    gyroDiffBase.x = (gyroValue.x - gyroBase.x) / 1000;
    gyroDiffBase.y = (gyroValue.y - gyroBase.y) / 1000;
    gyroDiffBase.z = (gyroValue.z - gyroBase.z) / 1000;

    gyroAngel.x = gyroAngel.x + (gyroDiffBase.x) * delta;
    gyroAngel.y = gyroAngel.y + (gyroDiffBase.y) * delta;
    gyroAngel.z = gyroAngel.z + (gyroDiffBase.z) * delta;

    Serial.print("Gyro VALUE[x:");
    Serial.print(gyroDiffBase.x);
    Serial.print(", y:");
    Serial.print(gyroDiffBase.y);
    Serial.print(", z:");
    Serial.print(gyroDiffBase.z);
    Serial.print("] ANGLE[x:");
    Serial.print(gyroAngel.x);
    Serial.print(", y:");
    Serial.print(gyroAngel.y);
    Serial.print(", z:");
    Serial.print(gyroAngel.z);
    Serial.println("]");
}

void setMotorPower(int power) 
{
    analogWrite(PIN_MOTOR_1, power);
    analogWrite(PIN_MOTOR_4, power);
    analogWrite(PIN_MOTOR_3, power);
    analogWrite(PIN_MOTOR_2, power);
}