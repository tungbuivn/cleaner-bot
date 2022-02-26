#ifndef _CENTERDRIVER_H_
#define _CENTERDRIVER_H_
#include "car-driver.h"

// we cannot create physical car as same as design, so there are some thing wrong :D
// this will plus to turn left, turn right step
#define PLUS_STEP_TURN_90_DEG 20
class CenterDriver : public CarDriver
{
protected:
    void turn(int direction, int multiple = 1);

public:
    using CarDriver::CarDriver;
    float CenterDriver::getRadius();
};
#endif