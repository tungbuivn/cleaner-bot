#ifndef _CAR_H_
#define _CAR_H_
#include "car-driver.h"
#include "wheel.h"
#include "eye-manager.h"
namespace driver
{
    enum STEERING_SYSTEM
    {
        ALL_WHEEL,
        FRONT_WHEEL,
        BACK_WHEEL
    };
};

class Car
{
private:
    driver::STEERING_SYSTEM steering;

    bool _initStatus;
    TARGET_SIDE target;
    bool cleanFinished;

public:
    Wheel frontLeft;
    Wheel frontRight;
    Wheel backLeft;
    Wheel backRight;
    CarDriver *driver;
    EyeManager eyes;

    Car();

    void setup();
    void movingAhead(float dist);
    void loop();
};
#endif
