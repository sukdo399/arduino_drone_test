// https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
// https://store.invensense.com/Datasheets/invensense/RM-MPU-6000A.pdf


#include <Arduino.h>
#include <Wire.h>

#define MPU6050_address     0x68
#define MPU6050_PWR1        0x6B
#define MPU6050_data_start  0x3B

void setup()
{
    Serial.begin(19200);

    //
    Wire.begin();
    Wire.beginTransmission(MPU6050_address);
    Wire.write(MPU6050_PWR1);
    Wire.write(0);
    Wire.endTransmission();
    //
}

void loop()
{
    int temp=0, accel_x=0, accel_y=0, accel_z=0, gyro_x=0, gyro_y=0, gyro_z=0;
    int read_bytes = 2;

    Wire.beginTransmission(MPU6050_address);
    Wire.write(MPU6050_data_start);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_address, 14);
    if(Wire.available() == 14)
    {
        accel_x = Wire.read()<<8 | Wire.read();
        accel_y = Wire.read()<<8 | Wire.read();
        accel_z = Wire.read()<<8 | Wire.read();
        temp = Wire.read()<<8 | Wire.read();
        gyro_x = Wire.read()<<8 | Wire.read();
        gyro_y = Wire.read()<<8 | Wire.read();
        gyro_z = Wire.read()<<8 | Wire.read();
    }

    Serial.print("ACCEL[X: ");
    Serial.print(accel_x);
    Serial.print(", Y: ");
    Serial.print(accel_y);
    Serial.print(", Z: ");
    Serial.print(accel_z);
    Serial.print("] TEMP[");
    Serial.print(temp/340.00 + 36.53);
    Serial.print("] GYRO[X: ");
    Serial.print(gyro_x);
    Serial.print(", Y: ");
    Serial.print(gyro_y);
    Serial.print(", Z: ");
    Serial.print(gyro_z);
    Serial.println("]");

    Wire.beginTransmission(MPU6050_address);
    Wire.endTransmission(true);

    delay(500);

}


