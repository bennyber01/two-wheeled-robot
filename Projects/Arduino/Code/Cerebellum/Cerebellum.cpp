#include "cerebellum.h"

Cerebellum::Cerebellum()
{

}

Cerebellum::~Cerebellum()
{

}

void Cerebellum::Init()
{
    I2CComm.Init(I2C_ADDRESS);
}

void Cerebellum::LoopStep()
{


      // wait 2 milliseconds before the next loop
      // for the analog-to-digital converter to settle
      // after the last reading:
      delay(2);
}
