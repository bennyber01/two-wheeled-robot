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
    float GetCurrent();

private:
    NewPing sonar;

    unsigned long lastSonarUpdateTime;

    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;
    SonarData sonarData;
    float currentVal;

    DistanceSensorFilter frontLeftDistanceSensorFilter;
    DistanceSensorFilter frontCenterDistanceSensorFilter;
    DistanceSensorFilter frontRightDistanceSensorFilter;
    DistanceSensorFilter sonarDistanceSensorFilter;

    void UpdateFrontLeftDistanceSensorValue(int val);
    void UpdateFrontCenterDistanceSensorValue(int val);
    void UpdateFrontRightDistanceSensorValue(int val);
    void UpdateSonarDistanceSensorValue(int val);
    void UpdateCurrentValue(int val);
};

#endif
