#pragma once
#include <Arduino.h>
namespace sensor
{

    // sensor pin
    enum class SensorSocket
    {
        ONE = PIN_A0,
        TWO = PIN_A1,
        THREE = PIN_A2,
        FOUR = PIN_A3,

    };
}
class Sensor
{
private:
    uint8_t pin;

public:
    Sensor();
    int minValue;
    void setup(uint8_t sensorPin, int aminValue);
    int getState();
};