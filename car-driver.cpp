#include "car-driver.h"
#include "wheel.h"
#include "options.h"
CarDriver::CarDriver(Wheel *frontLeft, Wheel *frontRight, Wheel *backLeft, Wheel *backRight)
{

    this->frontLeft = frontLeft;
    this->frontRight = frontRight;
    this->backLeft = backLeft;
    this->backRight = backRight;

    motors[0] = &frontLeft->tire;
    motors[1] = &frontRight->tire;
    motors[2] = &backLeft->tire;
    motors[3] = &backRight->tire;
    motors[4] = &frontLeft->direction;
    motors[5] = &frontRight->direction;
    motors[6] = &backLeft->direction;
    motors[7] = &backRight->direction;

    sensors[0] = &frontLeft->sensor;
    sensors[1] = &frontRight->sensor;
    sensors[2] = &backLeft->sensor;
    sensors[3] = &backRight->sensor;
    numberOfMotor = 8;
}
bool CarDriver::homingAllWheels()
{
    Serial.println("Homing all wheel");
    int states[4] = {1, 1, 1, 1};
    bool homingStatus = false;
    for (int i = 0; i < STEP_PER_REVERLUTION; i++)
    {
        for (int wh = 0; wh < 4; wh++)
        {
            // stop moving when signal actived
            states[wh] = sensors[wh]->getState() > 0 ? 0 : 1;
        }

        homingStatus = (states[0] | states[1] | states[2] | states[3]) == 0;
        // nomore move ?
        if (homingStatus)
        {
            break;
        }
        parallelMove(0, 0, 0, 0, states[0], states[1], states[2], states[3]);
    }
    stopDirections();
    if (homingStatus)
    {
        Serial.println("Appply calibring wheel data");

        // setup wheel with calibre data
        int stepMax = max(max(max(frontLeft->calibre, frontRight->calibre), backLeft->calibre), backRight->calibre);
        int cab[4] = {1, 1, 1, 1};
        for (int i = 0; i < stepMax; i++)
        {
            cab[0] = i < frontLeft->calibre;
            cab[1] = i < frontRight->calibre;
            cab[2] = i < backLeft->calibre;
            cab[3] = i < backRight->calibre;
            parallelMove(0, 0, 0, 0, -cab[0], -cab[1], -cab[2], -cab[3]);
        }
        stopDirections();
    }
    else
    {
        Serial.print("Status: ");
        for (int i = 0; i < 4; i++)
        {
            Serial.print(states[i]);
            Serial.print(" ");
        }
        Serial.println();
        Serial.println("Homing failed !!!");
    }

    return homingStatus;
}
void CarDriver::parallelMove(int afrontLeft, int afrontRight, int abackLeft, int abackRight,
                             int arotFrontLeft, int arotFrontRight, int arotBackLeft, int arotBackRight)
{
    uint8_t *p = (uint8_t *)&Last74HCValue;
    int data[] = {afrontLeft, afrontRight, abackLeft, abackRight, arotFrontLeft, arotFrontRight, arotBackLeft, arotBackRight};

    for (int i = 0; i < phaseCWLength; i++)
    {
        for (int idx = 0; idx < numberOfMotor; idx++)
        {

            if (data[idx] != 0)
            {
                motors[idx]->singlePhase(i, data[idx]);
            }
        }

        digitalWrite(LATCH_PIN, LOW);
        // shift out the bits:
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 3));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 2));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *(p + 1));
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, *p);
        digitalWrite(LATCH_PIN, HIGH);

        delayMicroseconds(MOTOR_DELAY_TIME);
        // (*frontLeft.tire._cw)(phaseCWList[i]);
    }
}

void CarDriver::stop(int inc = 0)
{
    if (inc > 0)
    {
        inc = 4;
    }
    for (int i = 0; i < 4; i++)
    {
        motors[i + inc]->stop();
    }
}
void CarDriver::stopDirections()
{
    stop(1);
}
void CarDriver::stopTires()
{
    stop();
}
void CarDriver::moveStraight(int steps)
{
    int dir = steps > 0 ? 1 : -1;
    uint8_t *p = (uint8_t *)&Last74HCValue;
    steps = abs(steps);
    for (int i = 0; i < steps; i++)
    {
        parallelMove(dir, dir, dir, dir, 0, 0, 0, 0);
    }
    stopTires();
}
void CarDriver::move(float length)
{
    moveStraight(getStepsFromLength(length));
}
int CarDriver::getStepsFromLength(float length)
{
    // pi*d-total
    int steps = (length * STEP_PER_REVERLUTION / (PI * CAR_WHEEL_DIAMETER));
    return steps;
}
void CarDriver::turnLeft()
{
    turn(-1);
    // restore wheel position
}
void CarDriver::turnRight()
{
    turn(1);
}