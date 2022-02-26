#pragma once
#include "step.h"
#include "sensor.h"

namespace move
{
    enum direction
    {
        BACKWARD = true,
        FORWARD = false
    };
}
class Wheel
{
    // private:
    //     bool _applyTurning();
    //     bool _checkSide(int dir);

public:
    int calibre;
    Sensor sensor;
    Step tire;
    Step direction;
    Wheel();
    // void move(int steps);
    // void rotate(float angle);

    // bool calibreDirection();
    bool setup(sensor::SensorSocket sensor, int sensorMinValue, int acalibre, step::StepSocket tire, bool isRevert, step::StepSocket direction, bool isRevertDirection);
};