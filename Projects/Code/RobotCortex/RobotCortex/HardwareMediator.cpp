#include "HardwareMediator.h"
#include "Cerebrum.h"
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */

#include "boost/random.hpp" 

#define _USE_MATH_DEFINES
#include "math.h"

//#include <boost/date_time/posix_time/posix_time.hpp>

typedef boost::uniform_int<> NumberDistribution;
typedef boost::mt19937 RandomNumberGenerator;
typedef boost::variate_generator<RandomNumberGenerator&, NumberDistribution> Generator;

const int rangeMin = -30;
const int rangeMax = 300;
NumberDistribution distribution(rangeMin, rangeMax);
RandomNumberGenerator generator;
Generator numberGenerator(generator, distribution);

HardwareMediator::HardwareMediator(Cerebrum * cerebrum)
{
	this -> cerebrum = cerebrum;

	generator.seed(std::time(0)); // seed with the current time
}

HardwareMediator::~HardwareMediator(void)
{
	// Ask thread to stop
	communicationThread.interrupt();

	// Join - wait when thread actually exits
	communicationThread.join();
	cerebrum -> GetGraphics().println("HardwareMediator::~HardwareMediator : communication thread ended");
}

bool HardwareMediator::InitHardwareModule()
{
	cerebrum -> GetGraphics().println("START : HardwareMediator::InitHardwareModule");

	// Start thread
	communicationThread = boost::thread(&UpdateRobotLocationThreadMethod, this);

	cerebrum -> GetGraphics().println("FINISHED : HardwareMediator::InitHardwareModule");
	
	return true;
}

void HardwareMediator::UpdateRobotLocationThreadMethod(void * lparam)
{
	HardwareMediator * hardwareMediator = (HardwareMediator*) lparam;

	MotorsTicks motorsTicks;

	while (1)
	{
		motorsTicks.leftMotorTicks  = unsigned int(numberGenerator());
		motorsTicks.rightMotorTicks = unsigned int(numberGenerator());
		hardwareMediator -> cerebrum -> UpdateRobotLocation(motorsTicks);
		//boost::this_thread::sleep_for(boost::chrono::milliseconds(20));
	}
}
