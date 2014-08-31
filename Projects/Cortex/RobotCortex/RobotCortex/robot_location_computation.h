#pragma once

#include "general_definitions.h"

WheelsLocation computeNewLocation(const WheelsLocation & oldLocation, const MotorsTicks & motorsTicks, WheelsLocationsHolder * wheelsLocationsHolder = NULL);
