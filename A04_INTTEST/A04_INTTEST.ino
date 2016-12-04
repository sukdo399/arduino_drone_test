#include <Arduino.h>

void ISR_function()
{
    Serial.println("interrupted");
}

void setup()
{
    Serial.begin(19200);
    pinMode(INT1, OUTPUT);
    attachInterrupt(INT1, ISR_function, RISING);
}

void loop()
{
    digitalWrite(INT1, HIGH);
    delay(200);
    digitalWrite(INT1, LOW);
    delay(1000);
}