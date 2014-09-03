#include "cerebellum.h"

Cerebellum::Cerebellum() : lcd(0x27,20,4)  // set the LCD address to 0x27 for a 20 chars and 4 line display
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
