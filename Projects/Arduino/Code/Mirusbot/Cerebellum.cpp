#include "cerebellum.h"
#include "robot_location_computation.h"

Cerebellum::Cerebellum()
{

}

Cerebellum::~Cerebellum()
{

}

void Cerebellum::Init()
{
    disp.Init();
    motors.Init();
    sensors.Init();
    I2CComm.Init();
}

void Cerebellum::Update()
{
    // update data from peripherals
    motors.Update();
    sensors.Update();

    MotorsTicks motorsTicks = motors.GetMotorsTicks();
    robotWeelsLocation = computeNewLocation(robotWeelsLocation, motorsTicks);

    // set relevent paramt to disp.
    disp.Print(motorsTicks);
    disp.Print(motors.GetMotorsSpeed());
    disp.Print(sensors.GetFrontSensorsData());
    disp.Print(sensors.GetBumpersData());

    // refresh screen
    disp.Update();
    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);
}
