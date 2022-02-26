#include "car.h"
#include "sensor.h"
#include "wheel.h"
#include "options.h"
#include "center-driver.h"

static int count = 0;
int testxx = 0;
// static const float maxDist = max(CAR_LENGTH / 2, CAR_WIDTH / 2);
Car::Car()
{
}
void Car::setup()
{
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(POWER_SENSOR_PIN, OUTPUT);

    // setup initalize data
    digitalWrite(POWER_SENSOR_PIN, LOW);

    // stop all output to decrease current consume
    digitalWrite(LATCH_PIN, LOW);

    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0);

    digitalWrite(LATCH_PIN, HIGH);

    digitalWrite(POWER_SENSOR_PIN, HIGH);
    _initStatus = false;
    target = TARGET_SIDE::LEFT;
    steering = driver::ALL_WHEEL;
    cleanFinished = false;
    bool w1 = false, w2 = false, w3 = false, w4 = false;
    eyes.setup();
    // eyes.enableSideEyes();

    // all wheel will be setup to move forward, all rotation with ccw direction to the end point stop
    w1 = frontLeft.setup(sensor::SensorSocket::ONE, 1000, HALF_REVOLUTION + 5, step::StepSocket::THREE, false, step::StepSocket::FOUR, false);
    w2 = backLeft.setup(sensor::SensorSocket::THREE, 1000, HALF_REVOLUTION - 14, step::StepSocket::EIGHT, false, step::StepSocket::SEVEN, false);

    // // moving same direction of front wheel
    w3 = frontRight.setup(sensor::SensorSocket::TWO, 1000, HALF_REVOLUTION - 10, step::StepSocket::FIVE, true, step::StepSocket::SIX, true);
    w4 = backRight.setup(sensor::SensorSocket::FOUR, 1000, HALF_REVOLUTION - 2, step::StepSocket::ONE, true, step::StepSocket::TWO, true);

    digitalWrite(POWER_SENSOR_PIN, LOW); // turn off endstop power source
    switch (steering)
    {
    case driver::ALL_WHEEL:
        driver = new CenterDriver(&frontLeft, &frontRight, &backLeft, &backRight);
        break;
    case driver::FRONT_WHEEL:

        // driver = new CenterDriver(frontLeft, backLeft, frontRight, backRight);
        break;
    case driver::BACK_WHEEL:

        // driver = new CenterDriver(frontLeft, backLeft, frontRight, backRight);
        break;
    default:
        break;
    }

    _initStatus = driver->homingAllWheels();
}

void Car::loop()
{

    if (!_initStatus)
    {
        if (count == 0)
        {

            count = 1;

            Serial.println("Initalize bot was not success. Please repair for working version =))");
        };
        return;
    }
    if (cleanFinished)
    {
        // can we find the way to return home :D
        return;
    }
    float aheadDist = eyes.getDistance();

    if (aheadDist > DISTANCE_TO_TURN_CAR)
    {
        Serial.println("moving car ahead 2cm");
        // move ahead 2cm
        driver->move(DISTANCE_TO_OPEN_EYE);
    }
    else
    {
        int stepBack = aheadDist - DISTANCE_TO_TURN_CAR;
        Serial.print("Stepback :");
        Serial.print(stepBack);
        Serial.println(" mm");
        // move backward if need
        driver->move(stepBack);
        Serial.println("Side distance:");

        TARGET_SIDE invertTarget = static_cast<TARGET_SIDE>(-target);
        // if we can turn left then turn else turn right
        // if (target == TARGET_SIDE::LEFT)
        // {
        if (eyes.getSideDist(target) > DISTANCE_TO_TURN_CAR)
        {
            Serial.print("Turn ");
            Serial.println(target);
            driver->turn(target);

            Serial.print("Moving ahead ");
            Serial.println(CAR_LENGTH);

            driver->move(CAR_LENGTH);

            Serial.print("Second phase turn: ");
            Serial.println(target);
            driver->turn(target);
            target = invertTarget;
        }
        else
        {

            Serial.println("Turn 180 deg");
            // go back the way
            // rotate 180
            driver->turn(target, 2);
            // moving util we can turn left
            aheadDist = eyes.getDistance();
            while (aheadDist > DISTANCE_TO_TURN_CAR)
            {
                Serial.println("Thirt phase turn: moving car ahead 2cm");
                driver->move(DISTANCE_TO_OPEN_EYE);
                aheadDist = eyes.getDistance();
                float dist = eyes.getSideDist(invertTarget);
                // when we found point to turn left
                if (dist > DISTANCE_TO_TURN_CAR)
                {
                    Serial.print("Turn ");
                    Serial.println(invertTarget);
                    driver->turn(invertTarget);
                    // moving
                    Serial.print("Moving ahead ");
                    Serial.println(CAR_LENGTH);
                    driver->move(CAR_LENGTH);

                    Serial.print("Turn ");
                    Serial.println(target);
                    // restore direction
                    driver->turn(target);

                    target = invertTarget;
                    return;
                }
            }
            // still cannot turn ? deadend wall ?
            // so the room has cleaned, stop the the bot
            cleanFinished = true;
            Serial.println("Finished");
        }
    }
}
