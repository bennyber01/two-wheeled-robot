#ifndef MOTORS_MODULE_H
#define MOTORS_MODULE_H

#include "CommunicationDefinitions.h"
#include <Wire.h>               // needs to be included here for the
                                // NXTI2CDevice to work
//#include <NXTI2CDevice/NXTI2CDevice.h>
//#include <NXTI2CDevice/NXTMMX.h>

class MotorsModule : public ArduinoModule
{
public:
    MotorsModule();
    ~MotorsModule();

    void Init();
    void Update();

    void SetMotorsSpeed(const MotorsSpeed & newSpeeds);
    MotorsSpeed GetMotorsSpeed();

    MotorsTicks GetMotorsTicks();

private:
    MotorsSpeed motorsSpeed;
    MotorsTicks motorsTicks;

 //   NXTMMX mmx;
};

#endif
