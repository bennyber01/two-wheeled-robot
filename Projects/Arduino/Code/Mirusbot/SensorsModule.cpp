#include "SensorsModule.h"

inline double ConvertAnalogValueToCM_SharpSensor_2D120X(int val)
{
    double volts = double(val) * 0.0048828125;      // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    double distance = 2076.0 / (val - 11.0);

 //   double distance = -(3.078*pow(volts,5))+(29.645*pow(volts,4))-(110.68*pow(volts,3))+(201.94*pow(volts,2))-(186.84*pow(volts,1))+81.524;

    return distance;
}

inline double ConvertAnalogValueToCM_SharpSensor_GP2D12(int val)
{
    double volts = double(val);// * 0.0048828125;      // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    double distance = (6787.0 / (volts - 3.0)) - 4.0;
    return distance;
}

SensorsModule::SensorsModule()
{
    frontSensorsData.LSensorDist = 0.0f;
    frontSensorsData.CSensorDist = 0.0f;
    frontSensorsData.RSensorDist = 0.0f;
    bumpersData.LBumper = 0;
    bumpersData.RBumper = 0;
}

SensorsModule::~SensorsModule()
{

}

void SensorsModule::Init()
{
    // no need to init alanog pins for input
    // sonar pins are init in ping module
    pinMode(L_BUMPER_PIN, INPUT_PULLUP);
    pinMode(R_BUMPER_PIN, INPUT_PULLUP);
}

void SensorsModule::Update()
{
    bumpersData.LBumper = digitalRead(L_BUMPER_PIN);
    //delay(2);
    UpdateFrontLeftDistanceSensorValue();
    //delay(2);
    UpdateFrontCenterDistanceSensorValue();
    //delay(2);
    UpdateFrontRightDistanceSensorValue();
    //delay(2);
    bumpersData.RBumper = digitalRead(R_BUMPER_PIN);
    //delay(2);

    delay(2);
}

void SensorsModule::UpdateFrontLeftDistanceSensorValue()
{
    int val = analogRead(FRONT_LEFT_DISTANCE_SENSOR_PIN);    // read the input pin
    int filteredVal = frontLeftDistanceSensorFilter.Filter(val);
    frontSensorsData.LSensorDist = ConvertAnalogValueToCM_SharpSensor_GP2D12(filteredVal);
}

void SensorsModule::UpdateFrontCenterDistanceSensorValue()
{
    int val = analogRead(FRONT_CENTER_DISTANCE_SENSOR_PIN) - 4;    // read the input pin
    int filteredVal = frontCenterDistanceSensorFilter.Filter(val);
    frontSensorsData.CSensorDist = ConvertAnalogValueToCM_SharpSensor_2D120X(filteredVal);
}

void SensorsModule::UpdateFrontRightDistanceSensorValue()
{
    int val = analogRead(FRONT_RIGHT_DISTANCE_SENSOR_PIN) - 15;    // read the input pin
    int filteredVal = frontRightDistanceSensorFilter.Filter(val);
    frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SharpSensor_2D120X(filteredVal);
}

FrontSensorsData SensorsModule::GetFrontSensorsData()
{
    return frontSensorsData;
}

BumpersData SensorsModule::GetBumpersData()
{
    return bumpersData;
}
