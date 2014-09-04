#include "MotorsModule.h"

MotorsModule::MotorsModule()
{
    motorsSpeed.LMotorSpeed = 0;
    motorsSpeed.RMotorSpeed = 0;
    motorsTicks.LMotorTick = 0;
    motorsTicks.RMotorTick = 0;
}

MotorsModule::~MotorsModule()
{

}

void MotorsModule::SetMotorsSpeed(const MotorsSpeed & newSpeeds)
{
    motorsSpeed = newSpeeds;
}

MotorsSpeed MotorsModule::GetMotorsSpeed()
{
    return motorsSpeed;
}

MotorsTicks MotorsModule::GetMotorsTicks()
{
    static LONG c = 0;
    motorsTicks.LMotorTick = c++;
    motorsTicks.RMotorTick = c++;
    return motorsTicks;
}
