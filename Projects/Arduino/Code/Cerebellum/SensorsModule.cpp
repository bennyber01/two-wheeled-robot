#include "SensorsModule.h"

inline double ConvertAnalogValueToCM_SharpSensor(int val)
{
    double volts = double(val) * 0.0048828125;      // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    double distance = 65.0 * pow(volts, -1.10);      // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk

    //double volts_2 = volts * volts;
    //double volts_3 = volts * volts_2;
    //double volts_4 = volts * volts_2;
    //double distance = 1.5290*volts_4-13.7043*volts_3+52.5578*volts_2+112.8212*volts+120.3399;

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
}

void SensorsModule::Update()
{
    int val;

    val = analogRead(FRONT_LEFT_DISTANCE_SENSOR_PIN);    // read the input pin
    UpdateFrontLeftDistanceSensorValue(val);

    val = analogRead(FRONT_CENTER_DISTANCE_SENSOR_PIN);    // read the input pin
    UpdateFrontCenterDistanceSensorValue(val);

    val = analogRead(FRONT_RIGHT_DISTANCE_SENSOR_PIN);    // read the input pin
    UpdateFrontRightDistanceSensorValue(val);

    val = analogRead(CURRENT_SENSOR_PIN);                 // read the input pin
    UpdateCurrentValue(val);

    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    unsigned long time_millisec = millis();
    if (lastSonarUpdateTime < time_millisec - 50)
    {
        unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
        UpdateSonarDistanceSensorValue(uS);
        lastSonarUpdateTime = time_millisec;
    }
}

void SensorsModule::UpdateFrontLeftDistanceSensorValue(int val)
{
    int filteredVal = frontLeftDistanceSensorFilter.Filter(val);
    frontSensorsData.LSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateFrontCenterDistanceSensorValue(int val)
{
    int filteredVal = frontCenterDistanceSensorFilter.Filter(val);
    frontSensorsData.CSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateFrontRightDistanceSensorValue(int val)
{

    int filteredVal = frontRightDistanceSensorFilter.Filter(val);
    frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SharpSensor(filteredVal);
}

void SensorsModule::UpdateSonarDistanceSensorValue(int val)
{
    int filteredVal = sonarDistanceSensorFilter.Filter(val);
    frontSensorsData.RSensorDist = ConvertAnalogValueToCM_SonarSensor(filteredVal);
}

void SensorsModule::UpdateCurrentValue(int val)
{
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
