#include "cerebellum.h"

Cerebellum::Cerebellum()
{

}

Cerebellum::~Cerebellum()
{

}

void Cerebellum::Init()
{
    I2CComm.Init(I2C_ADDRESS);
}

void Cerebellum::LoopStep()
{
    // update data from peripherals
    motors.Update();
    sensors.Update();

    // set relevent paramt to disp.
    disp.Print(motors.GetMotorsTicks());
    disp.Print(motors.GetMotorsSpeed());
    disp.Print(camera.GetCameraPosition());
    disp.Print(sensors.GetFrontSensorsData());
    disp.Print(sensors.GetBumpersData());
    disp.Print(sensors.GetSonarData());
    disp.Print("Not connected");

    // refresh screen
    disp.Update();
    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);
}
