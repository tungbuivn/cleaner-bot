#pragma once
#include "eye-manager.h"
#include "options.h"
#include "Arduino.h"

EyeManager::EyeManager()
{

    right = new Eye(2, 3, 0);
    center = new Eye(4, 5, 20);
    left = new Eye(6, 7, 0);
}
void EyeManager::setup()
{
    left->setup();
    right->setup();
    center->setup();
}
float EyeManager::getSideDist(TARGET_SIDE side)
{
    return side == TARGET_SIDE::LEFT ? left->getDistance() : right->getDistance();
}
float EyeManager::getDistance()
{
    return center->getDistance();
}
