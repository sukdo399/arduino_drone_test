#include <Arduino.h>

void setup()
{
    Serial.begin(19200);
}

void loop()
{
    Serial.println("Hello World.");
    Serial.println(Serial.available());
    Serial.println(Serial);

    Serial.print(78, BIN);
    Serial.println(78, OCT);
    Serial.println(78, DEC);
    Serial.println(78, HEX);

    Serial.println(4.14, 0);
    Serial.println(4.14, 1);

    Serial.println("");

    delay(5000);

}
