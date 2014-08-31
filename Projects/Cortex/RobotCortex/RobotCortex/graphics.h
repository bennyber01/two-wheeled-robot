#pragma once

#include "general_definitions.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void Draw(const MotorsTicks & motorsTicks);

	void print(const char * format, ...);
	void println(const char * format, ...);
	bool SaveAsBMP( const WheelsLocationsHolder & wheelsLocationsHolder, char * fileName );
private:
};
