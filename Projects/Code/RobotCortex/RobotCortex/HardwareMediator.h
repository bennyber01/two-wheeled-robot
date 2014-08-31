#pragma once

#include "boost/thread.hpp"

class Cerebrum;

class HardwareMediator
{
public:
	HardwareMediator(Cerebrum * cerebrum);
	~HardwareMediator(void);

	bool InitHardwareModule();

private:
	Cerebrum * cerebrum;

	boost::thread communicationThread;

	static void UpdateRobotLocationThreadMethod(void * lparam);
};

