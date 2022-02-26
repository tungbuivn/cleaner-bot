#include "sensor.h"
#include "Arduino.h"
Sensor::Sensor()
{
    minValue = 1000;
}
void Sensor::setup(uint8_t sensorPin, int aminValue)
{

    pin = sensorPin;
    minValue = aminValue;
    Serial.print("sensor setup on pin:");
    Serial.println(pin);
    pinMode(pin, INPUT);
}
int Sensor::getState()
{

    int anal = analogRead(pin);
    int m = anal;
    int data = m >= minValue ? 1 : 0;

    return data;
}