#pragma once

#include "graphics.h"
#include "HardwareMediator.h"

class Cerebrum
{
public:
	Cerebrum(void);
	~Cerebrum(void);

	void InitHardwareModule();
	void InitCameraModule();
	void Run();

	void UpdateRobotLocation(const MotorsTicks & motorsTicks);

	Graphics & GetGraphics() { return graphics; }

private:

	Graphics graphics;
	HardwareMediator hardwareMediator;

	WheelsLocation wheelsLocation;
	WheelsLocationsHolder wheelsLocationsHolder;
};

