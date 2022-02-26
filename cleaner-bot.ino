
#include "car.h"
#include "options.h"
Car car;

void setup()
{
  Serial.begin(115200);
  car.setup();
}
void loop()
{
  car.loop();
}
