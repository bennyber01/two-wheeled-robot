#include "Cerebrum.h"
//#include <cstdlib>

int main(int argc, char *argv[])
{
	Cerebrum cerebrum;
	cerebrum.InitHardwareModule();
	cerebrum.InitCameraModule();
	cerebrum.Run();
    system("PAUSE");
    return 0;
}
