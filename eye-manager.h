#pragma once
#include "eye.h"
#include "eye-manager.h"

enum TARGET_SIDE
{
    LEFT = -1,
    RIGHT = 1
};
class EyeManager
{
public:
    Eye *left;
    Eye *right;
    Eye *center;
    float leftDist;
    float rightDist;
    EyeManager();
    void setup();
    float getDistance();
    float getSideDist(TARGET_SIDE side);
};
