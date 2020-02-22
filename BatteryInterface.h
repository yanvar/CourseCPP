#pragma once
#include "Common.h"

class BatteryInterface
{
public:
	virtual int stepsLeft() const = 0;
	virtual bool isBatteryEmpty() const = 0;
	virtual float setBatteryLevelInSteps(float stepsToSet) = 0;
	virtual float decrementBatterySingleStep() = 0;
	virtual float chargeBatteryDuringSingleStep() = 0;
};

