#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <Arduino.h>
#include "CommunicationDefinitions.h"
#include "I2CCommunicationModule.h"
#include "DisplayModule.h"
#include "MotorsModule.h"
#include "SensorsModule.h"
#include "RobotDefinitions.h"

class Cerebellum : public ArduinoModule
{
public:
    Cerebellum();
    ~Cerebellum();

    void Init();
    void Update();

private:
    DisplayModule disp;
    MotorsModule motors;
    SensorsModule sensors;
    I2CCommunicationModule I2CComm;

    WheelsLocation robotWeelsLocation;
};

#endif
