#ifndef MOTORS_MODULE_H
#define MOTORS_MODULE_H

#include "CommunicationDefinitions.h"
#include <NXTI2CDevice-master/NXTMMX.h>

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

    NXTMMX mmx;
};

#endif
