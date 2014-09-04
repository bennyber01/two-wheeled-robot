#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

#include "CommunicationDefinitions.h"

class SensorsModule
{
public:
    SensorsModule();
    ~SensorsModule();

    FrontSensorsData GetFrontSensorsData();
    BumpersData GetBumpersData();
    SonarData GetSonarData();

private:
    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;
    SonarData sonarData;
};

#endif
