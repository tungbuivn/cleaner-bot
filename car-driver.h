#ifndef _CARDRIVER_H_
#define _CARDRIVER_H_
#include "step.h"
#include "wheel.h"
#include "sensor.h"

class CarDriver
{
protected:
    float radius;
    int numberOfMotor;
    Step *motors[4];
    Step *directions[4];
    Sensor *sensors[4];
    Wheel *frontLeft;
    Wheel *frontRight;
    Wheel *backLeft;
    Wheel *backRight;
    // inc =0 trop tire's motors, >0 stop direction's motors
    void stop(int inc = 0);

public:
    CarDriver(Wheel *frontLeft, Wheel *frontRight, Wheel *backLeft, Wheel *backRight);
    // move all motors immediately
    void parallelMove(int afrontLeft, int afrontRight, int abackLeft, int abackRight, int arotFrontLeft, int arotFrontRight, int arotBackLeft, int arotBackRight);

    // radius in turning car
    virtual float getRadius() = 0;

    // move all wheel to zero position
    bool homingAllWheels();

    // steps >0 is forward, <0 is backward
    void moveStraight(int steps);

    // moving by the distance, length>0 move forwead, len<0 move backward
    void move(float length);

    // stop all current signal on tire motors
    void stopTires();

    // stop all current signal on direction motors
    void stopDirections();

    // control turn angle by the 'multiple'
    virtual void turn(int direction, int multiple = 1) = 0;

    // turn left 90 deg
    virtual void turnLeft();

    // turn right 90 deg
    virtual void turnRight();

    // calculate step need to move length mm
    int getStepsFromLength(float length);
};
#endif
