#include "cerebellum.h"
#include <Servo.h>

Cerebellum cerebellum;

void setup()
{
    cerebellum.Init();
}

void loop()
{
    cerebellum.Update();
}
