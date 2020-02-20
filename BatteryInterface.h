#pragma once
#include "Common.h"

class BatteryInterface
{
public:
	virtual int stepsLeft() const = 0;
};

