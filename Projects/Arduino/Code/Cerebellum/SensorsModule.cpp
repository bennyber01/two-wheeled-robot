#include "SensorsModule.h"

inline double ConvertAnalogValueToCM_SharpSensor(int val)
{
    return val;
}

inline double ConvertAnalogValueToCM_SonarSensor(int val)
{
    return double(val) / double(US_ROUNDTRIP_CM);
}

SensorsModule::SensorsModule() : sonar(TRIGGER_PIN, ECHO_PIN, MAX_SONAR_SENSOR_DISTANCE) // NewPing setup of pins and maximum distance.
{
    frontSensorsData.LSensorDist = 0.0f;
    frontSensorsData.CSensorDist = 0.0f;
    frontSensorsData.RSensorDist = 0.0f;
    bumpersData.LBumper = 0;
    bumpersData.RBumper = 0;
    sonarData.dist = 0;
    lastSonarUpdateTime = 0;
}

SensorsModule::~SensorsModule()
{

}

void SensorsModule::Init()
{

}

void SensorsModule::UpdateSensors()
{
    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    int time_milisec = ;
    if (time_milisec - lastSonarUpdateTime > 50)
    {
        unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
        UpdateSonarDistanceSensorFilter(uS);
    }
}

void SensorsModule::UpdateFrontLeftDistanceSensorFilter(int val)
{
    int filteredVal = frontLeftDistanceSensorFilter.Filter(val);
    frontSensorsData.LSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateFrontCenterDistanceSensorFilter(int val)
{
    int filteredVal = frontCenterDistanceSensorFilter.Filter(val);
    frontSensorsData.CSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateFrontRightDistanceSensorFilter(int val)
{

    int filteredVal = frontRightDistanceSensorFilter.Filter(val);
    frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateSonarDistanceSensorFilter(int val)
{
    int filteredVal = sonarDistanceSensorFilter.Filter(val);
    frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SonarSensor(filteredVal);
}

FrontSensorsData SensorsModule::GetFrontSensorsData()
{
    return frontSensorsData;
}

BumpersData SensorsModule::GetBumpersData()
{
    return bumpersData;
}

SonarData SensorsModule::GetSonarData()
{
    return sonarData;
}
