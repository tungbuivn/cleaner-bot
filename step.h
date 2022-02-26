#pragma once
#include "Arduino.h"
extern unsigned long Last74HCValue;
extern const int phaseCWLength;
extern const unsigned long MOTOR_DELAY_TIME;
namespace step
{
    enum class StepSocket
    {
        ONE = 0,
        TWO = 4,
        THREE = 8,
        FOUR = 12,
        FIVE = 16,
        SIX = 20,
        SEVEN = 24,
        EIGHT = 28
    };
}

class Step
{
private:
    typedef void (Step::*RotateFunction)(int idx, bool singlePhase);
    // int _shiftLeft;

    int _dataIdx;
    int _shift;
    bool isRevert;
    void _movecw(int idx = 0, bool singlePhase = false);
    void _moveccw(int idx = 0, bool singlePhase = false);
    unsigned int _delayTime;
    RotateFunction _cw;
    RotateFunction _ccw;
    int _phaseCount;

public:
    // this will disable phase delay and store data in the steps arrays, be carefull when using this,
    // when calling move, value of the current 74hc will be remember as last state
    uint8_t _lastState;
    Step();
    void test();

    void setup(step::StepSocket motor, bool isRevert);
    // void setSpeed(int rpm);
    void phase(unsigned long state, bool onlyData = false);
    void singlePhase(int idx, int direction);
    void virtual stop();
    void restorePhase();

    // steps >0 for ccw; <0 for cw;
    void move(int steps);
};