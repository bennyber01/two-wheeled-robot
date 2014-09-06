#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

#include "CommunicationDefinitions.h"
#include "DistanceSensorFilter.h"
#include <NewPing/NewPing.h>

class SensorsModule
{
public:
    SensorsModule();
    ~SensorsModule();

    void Init();
    void UpdateSensors();

    FrontSensorsData GetFrontSensorsData();
    BumpersData GetBumpersData();
    SonarData GetSonarData();

private:
    NewPing sonar;

    unsigned long lastSonarUpdateTime;

    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;
    SonarData sonarData;

    DistanceSensorFilter frontLeftDistanceSensorFilter;
    DistanceSensorFilter frontCenterDistanceSensorFilter;
    DistanceSensorFilter frontRightDistanceSensorFilter;
    DistanceSensorFilter sonarDistanceSensorFilter;

    void UpdateFrontLeftDistanceSensorFilter(int val);
    void UpdateFrontCenterDistanceSensorFilter(int val);
    void UpdateFrontRightDistanceSensorFilter(int val);
    void UpdateSonarDistanceSensorFilter(int val);
};

#endif
