#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include <LiquidCrystal_I2C.h>

class DisplayModule
{
public:
    DisplayModule();
    ~DisplayModule();

    void Print(const MotorsTicks & ticks);
    void Print(const MotorsSpeed & speeds);
    void Print(const CameraPosition & camPos);
    void Print(const FrontSensorsData & data);
    void Print(const BumpersData & data);
    void Print(const SonarData & data);

private:
    LiquidCrystal_I2C lcd;
};

#endif
