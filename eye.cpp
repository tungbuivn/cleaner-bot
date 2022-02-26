#pragma once
#include "eye.h"
#include "Arduino.h"
#include "options.h"
const unsigned long EYE_TIMEOUT = (2000 * MAX_DISTANCE_TO_MEASURE / SOUND_SPEED);
Eye::Eye(int triggerPin, int echoPin, float calibreData)
{
    _trigger = triggerPin;
    _echo = echoPin;
    _calibreData = calibreData;
    lastTrigger = 0;
    // _timeout = static_cast<unsigned long>(2000 * MAX_DISTANCE_TO_MEASURE / SOUND_SPEED);
};
void Eye::setup()
{
    Serial.print("Setup trigger on pin: ");
    Serial.print(_trigger);
    Serial.print("Setup echo on pin: ");
    Serial.println(_echo);

    pinMode(_trigger, OUTPUT);
    pinMode(_echo, INPUT);
    digitalWrite(_trigger, LOW);
}
float Eye::getDistance()
{
    long duration, distancemm;
    unsigned long tm = lastTrigger + HARDWARE_MIN_DELAY - micros();
    if (tm > 0)
    {
        delayMicroseconds(tm);
    }

    // digitalWrite(_trigger, LOW);
    // delayMicroseconds(10);
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);

    duration = pulseIn(_echo, HIGH, EYE_TIMEOUT);
    lastTrigger = micros();

    // Serial.print("trigger: ");
    // Serial.print(_trigger);
    // Serial.print(" duration: ");
    // Serial.print(duration);
    // convert to distance
    distancemm = (duration / 2) * SOUND_SPEED / 1e3;
    if (distancemm <= 1e-3)
    {
        distancemm = 1e6;
    }
    Serial.print("Distance: ");
    Serial.print(distancemm / 10);
    Serial.println(" cm");
    return distancemm;
}