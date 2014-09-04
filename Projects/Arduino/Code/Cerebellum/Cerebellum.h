#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <Arduino.h>
#include "CommunicationDefinitions.h"
#include "I2CCommunicationModule.h"
#include <DisplayModule.h>

#define I2C_ADDRESS 0x09

class Cerebellum
{
public:
    Cerebellum();
    ~Cerebellum();

    void Init();
    void LoopStep();

private:
    DisplayModule disp;

    I2CCommunicationModule I2CComm;
};

#endif
