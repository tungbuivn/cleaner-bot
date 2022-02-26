#pragma once
namespace eye
{

    enum SOCKET
    {
        LEFT = 1,
        CENTER = 2,
        RIGHT = 3
    };
}
class Eye
{
private:
    unsigned long lastTrigger;
    unsigned long _timeout;
    int _trigger;
    int _echo;
    float _calibreData;

public:
    Eye(int triggerPin, int echoPin, float calibreData);
    void setup();
    float getDistance();
};
