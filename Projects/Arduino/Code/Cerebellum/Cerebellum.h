#ifndef CEREBELLUM_H
#define CEREBELLUM_H

#include <Arduino.h>
#include "CommunicationDefinitions.h"
#include "I2CCommunicationModule.h"
#include "DisplayModule.h"
#include "CameraModule.h"
#include "MotorsModule.h"
#include "SensorsModule.h"

class Cerebellum : public ArduinoModule
{
public:
    Cerebellum();
    ~Cerebellum();

    void Init();
    void Update();

private:
    DisplayModule disp;
    CameraModule camera;
    MotorsModule motors;
    SensorsModule sensors;
    I2CCommunicationModule I2CComm;
};

#endif
