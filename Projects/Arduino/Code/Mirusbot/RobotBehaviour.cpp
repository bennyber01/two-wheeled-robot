#include "cerebellum.h"
#include "Matrix2x2.h"

RobotBehaviour::RobotBehaviour()
{
    isHandlingEvent = false;
}

RobotBehaviour::~RobotBehaviour()
{

}

//    DisplayModule disp;
//    MotorsModule motors;
//    SensorsModule sensors;
//    WheelsLocation robotWeelsLocation;
void Cerebellum::UpdateRobotBehaviour()
{
    BumpersData bumpersData = sensors.GetBumpersData();

    bool isHitSonthing = bumpersData.LBumper ||
                         bumpersData.CBumper ||
                         bumpersData.RBumper;

    if (isHitSonthing)
    {
        MotorsSpeed motorsSpeed;
        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 0;
        motors.SetMotorsSpeed(motorsSpeed);
    }
    else
    {
        MotorsSpeed motorsSpeed;
        motorsSpeed.LMotorSpeed = motorsSpeed.RMotorSpeed = 70;
        motors.SetMotorsSpeed(motorsSpeed);
    }

    FrontSensorsData frontSensorsData = sensors.GetFrontSensorsData();
}
