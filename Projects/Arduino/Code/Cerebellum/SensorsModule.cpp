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

inline double ConvertAnalogValueToCM_SonarSensor(int val)
{
    return double(val) / double(US_ROUNDTRIP_CM);
}

inline double ConvertAnalogValueToAmpers(int val)
{
    return double(val) / double(US_ROUNDTRIP_CM);

    // Remap the ADC value into a voltage number (5V reference)
    double sensorValue = double(val * VOLTAGE_REF) / 1023.0;

    // Follow the equation given by the INA169 datasheet to
    // determine the current flowing through RS. Assume RL = 10k
    // Is = (Vout x 1k) / (RS x RL)
    double current = sensorValue / double(10 * RS);

    // Output value (in amps)
    return current;
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
    currentVal = 0.0f;
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
    UpdateCurrentValue();
    //delay(2);
    bumpersData.RBumper = digitalRead(R_BUMPER_PIN);
    //delay(2);

    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    unsigned long time_millisec = millis();
    if (lastSonarUpdateTime < time_millisec - 50)
    {
        UpdateSonarDistanceSensorValue();
        lastSonarUpdateTime = time_millisec;
    }
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

void SensorsModule::UpdateSonarDistanceSensorValue()
{
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    int filteredVal = sonarDistanceSensorFilter.Filter(uS);
    sonarData.dist = ConvertAnalogValueToCM_SonarSensor(filteredVal);
}

void SensorsModule::UpdateCurrentValue()
{
    int val = analogRead(CURRENT_SENSOR_PIN);                 // read the input pin
    currentVal = ConvertAnalogValueToAmpers(val);
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

float SensorsModule::GetCurrent()
{
    return currentVal;
}
