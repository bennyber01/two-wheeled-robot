#include "Cerebrum.h"
#include "robot_location_computation.h"
#include <stdio.h>


Cerebrum::Cerebrum(void) : hardwareMediator(this)
{
	wheelsLocation.leftWheelLoc.Set(0, 5);
	wheelsLocation.rightWheelLoc.Set(0, -5);
}

Cerebrum::~Cerebrum(void)
{
}

void Cerebrum::InitHardwareModule()
{
	graphics.println("START : Cerebrum::InitHardwareModule");
	hardwareMediator.InitHardwareModule();
	graphics.println("FINISHED : Cerebrum::InitHardwareModule");
}

void Cerebrum::InitCameraModule()
{
	graphics.println("START : Cerebrum::InitCameraModule");
	graphics.println("FINISHED : Cerebrum::InitCameraModule");
}

void Cerebrum::Run()
{
	graphics.println("START : Cerebrum::Run");
	//while(1)
	//	boost::this_thread::sleep_for(boost::chrono::milliseconds(600));
}

void Cerebrum::UpdateRobotLocation(const MotorsTicks & motorsTicks)
{
	wheelsLocation = computeNewLocation(wheelsLocation, motorsTicks, &wheelsLocationsHolder);

	static int counter = 0;
	char fileName[300];
	sprintf(fileName, "Frames/image_%04d.bmp", counter++);
	graphics.SaveAsBMP(wheelsLocationsHolder, fileName);
}
