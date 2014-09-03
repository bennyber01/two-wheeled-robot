#include "cerebellum.h"

Cerebellum cerebellum;

void setup()
{
    cerebellum.Init();
}

void loop()
{
    cerebellum.LoopStep();
}
