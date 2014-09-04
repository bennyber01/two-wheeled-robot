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

}
