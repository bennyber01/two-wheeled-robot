#ifndef SENSORS_MODULE_H
#define SENSORS_MODULE_H

#include "CommunicationDefinitions.h"
#include "DistanceSensorFilter.h"
#include <NewPing/NewPing.h>

class SensorsModule : public ArduinoModule
{
public:
    SensorsModule();
    ~SensorsModule();

    void Init();
    void Update();

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

    void UpdateFrontLeftDistanceSensorValue();
    void UpdateFrontCenterDistanceSensorValue();
    void UpdateFrontRightDistanceSensorValue();
    void UpdateSonarDistanceSensorValue();
    void UpdateCurrentValue();
};

#endif
