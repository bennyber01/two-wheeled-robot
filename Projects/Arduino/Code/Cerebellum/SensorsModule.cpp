#include "SensorsModule.h"

SensorsModule::SensorsModule()
{
    frontSensorsData.LSensorDist = 0.0f;
    frontSensorsData.CSensorDist = 0.0f;
    frontSensorsData.RSensorDist = 0.0f;
    bumpersData.LBumper = 0;
    bumpersData.RBumper = 0;
    sonarData.dist = 0;
}

SensorsModule::~SensorsModule()
{

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
