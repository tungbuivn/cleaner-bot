
#include "center-driver.h"
#include "math.h"
#include "options.h"
float CenterDriver::getRadius()
{
    float l = CAR_LENGTH / 2, w = CAR_WIDTH / 2;
    return sqrtf(l * l + w * w);
};
void CenterDriver::turn(int direction, int multiple = 1)
{
    stopTires();
    float distToMove = PI * getRadius() / 2;
    int steps = getStepsFromLength(distToMove) * multiple;
    // rotating wheel 45 deg
    int count = QUATER_REVOLUTION / 2;
    for (int i = 0; i < count; i++)
    {
        parallelMove(0, 0, 0, 0, 1, 1, -1, -1);
    }
    stopDirections();
    // do moving
    for (int i = 0; i < steps + PLUS_STEP_TURN_90_DEG; i++)
    {
        parallelMove(1 * direction, -1 * direction, 1 * direction, -1 * direction, 0, 0, 0, 0);
    }
    stopTires();
    // restore wheel to front
    for (int i = 0; i < count; i++)
    {
        parallelMove(0, 0, 0, 0, -1, -1, 1, 1);
    }
    stopDirections();
}
