#pragma once
#include "Common.h"

class BatteryInterface
{
public:
	virtual int stepsLeft() const = 0;
	virtual bool isBatteryEmpty() const = 0;
	virtual uint32_t setBatteryLevelInSteps(int stepsToSet) = 0;
	virtual uint32_t decrementBatterySingleStep() = 0;
	virtual uint32_t chargeBatteryDuringSingleStep() = 0;
};

