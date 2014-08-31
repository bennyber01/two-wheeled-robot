#pragma once
#include "my_vector.h"
#include "Vector2D.h"

#define WHEEL_RADIUS    7

struct WheelsLocation
{
    Vector2D leftWheelLoc;
    Vector2D rightWheelLoc;
};

struct MotorsTicks
{
    int leftMotorTicks;
    int rightMotorTicks;
};

typedef my_vector <MotorsTicks> MotorsTicksHolder;
typedef my_vector <WheelsLocation> WheelsLocationsHolder;

#define DEBUG_MY_PROGRAM
