#include <Arduino.h>
#include "wheel.h";
#include "sensor.h"
#include "options.h"

Wheel::Wheel()
{
}

bool Wheel::setup(sensor::SensorSocket asensor, int sensorMinValue, int acalibre, step::StepSocket atire, bool isRevert, step::StepSocket adirection, bool isRevertDirection)
{

    Serial.println("Wheel setup");
    uint8_t pin = static_cast<uint8_t>(asensor);

    calibre = acalibre;
    this->sensor.setup(pin, sensorMinValue);
    this->tire.setup(atire, isRevert);
    this->direction.setup(adirection, isRevertDirection);
    Serial.print("begin finding endstop for the tire:");
    Serial.println(static_cast<int>(atire));

    bool rs = true;

    return rs;
}
