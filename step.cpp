#include "step.h"
#include <Arduino.h>
#include "options.h"
unsigned long Last74HCValue = 0;

// const uint8_t phaseCWList[] = {
//     0b1000,
//     0b1100,
//     0b0100,
//     0b0110,
//     0b0010,
//     0b0011,
//     0b0001,
//     0b1001};
const uint8_t phaseCWList[] = {0b1000, 0b0100, 0b0010, 0b0001};
const int phaseCWLength = sizeof(phaseCWList);
const unsigned long MOTOR_DELAY_TIME = 60 * 1e6 / (MOTOR_MAX_RPM * phaseCWLength * STEP_PER_REVERLUTION);
Step::Step()
{

    isRevert = false;
    _cw = &_movecw;
    _ccw = &_moveccw;
    _lastState = 0;
    _phaseCount = 0;
    // setSpeed(DEFAULT_MOTOR_RPM);
}
void Step::setup(step::StepSocket motor, bool isRevert)
{

    int _shiftLeft = static_cast<int>(motor);
    _dataIdx = _shiftLeft / 8;
    _shift = _shiftLeft % 8;

    this->isRevert = isRevert;
    if (isRevert)
    {
        RotateFunction rot = _cw;
        _cw = _ccw;
        _ccw = rot;
    }
}
void Step::test()
{
    Serial.println("turn on");
    phase(0b1111);
    delay(500);
    Serial.println("turn off");
    phase(0);
    delay(500);
}
// void Step::setSpeed(int rpm)
// {
//     if (rpm <= 0)
//     {
//         rpm = 1;
//     }
//     if (rpm > 30)
//     {
//         rpm = 30;
//     }
//     _delayTime = floor(60.0 * 1e6 / (STEP_PER_REVERLUTION * phaseCWLength * rpm));
// }
void Step::stop()
{
    // reset all signal to low
    phase(0);
}
void Step::move(int steps)
{

    int n = abs(steps);
    RotateFunction rot = _ccw;

    if (steps < 0)
    {
        rot = _cw;
    }

    for (int i = 0; i < n; i++)
    {
        (this->*rot)(0, false);
    }
}
void Step::restorePhase()
{
    if (_lastState != 0)
    {
        phase(_lastState);
        _lastState = 0;
    }
}
void Step::singlePhase(int idx, int direction)
{
    // int i = abs(idx);
    RotateFunction rot = _ccw;

    if (direction < 0)
    {
        rot = _cw;
    }
    (this->*rot)(idx, true);
}
void Step::phase(unsigned long state, bool onlyData = false)
{
    uint8_t *p = (uint8_t *)&Last74HCValue;
    int idx = _dataIdx;
    if (state > 0)
    {
        _lastState = state;
    }

    // int ns = _shift;
    if (_shift > 0)
    {
        *(p + idx) = (*(p + idx) & 0x0F) | (state << _shift);
    }
    else
    {
        *(p + idx) = (*(p + idx) & 0xF0) | state;
    }
    if (!onlyData)
    {
        digitalWrite(LATCH_PIN, LOW);
        // shift out the bits:
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 3));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 2));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 1));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *p);
        digitalWrite(LATCH_PIN, HIGH);

        delayMicroseconds(MOTOR_DELAY_TIME);
    }
}
void Step::_movecw(int idx = 0, bool singlePhase = false)
{
    if (singlePhase)
    {
        phase(phaseCWList[idx], true);
    }
    else
    {
        for (int i = 0; i < phaseCWLength; i++)
        {
            phase(phaseCWList[i]);
        }
    }
}
void Step::_moveccw(int idx = 0, bool singlePhase = false)
{

    if (singlePhase)
    {
        phase(phaseCWList[phaseCWLength - 1 - idx], true);
        return;
    }
    else
    {
        for (int i = phaseCWLength - 1; i >= 0; i--)
        {
            phase(phaseCWList[i]);
        }
    }
}