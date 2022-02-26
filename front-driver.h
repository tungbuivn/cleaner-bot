#ifndef _FRONTDRIVER_H_
#define _FRONTDRIVER_H_
#include "car-driver.h"
class FrontDriver : public CarDriver
{
public:
    float getRadius();
    void move(float length);
};
#endif