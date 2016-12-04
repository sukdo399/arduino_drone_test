#include <Arduino.h>

#define PIN_MOTOR_1     6
#define PIN_MOTOR_2     10
#define PIN_MOTOR_3     5
#define PIN_MOTOR_4     9

void setup()
{
    pinMode(PIN_MOTOR_1, OUTPUT);
    pinMode(PIN_MOTOR_2, OUTPUT);
    pinMode(PIN_MOTOR_3, OUTPUT);
    pinMode(PIN_MOTOR_4, OUTPUT);
}

// int throtle = 10;
int throtle = 0;

void loop()
{
    analogWrite(PIN_MOTOR_1, throtle);
    analogWrite(PIN_MOTOR_2, throtle);
    analogWrite(PIN_MOTOR_3, throtle);
    analogWrite(PIN_MOTOR_4, throtle);
}