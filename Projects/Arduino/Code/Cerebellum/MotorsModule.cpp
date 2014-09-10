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

void MotorsModule::Init()
{

}

void MotorsModule::Update()
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
    return motorsTicks;
}
