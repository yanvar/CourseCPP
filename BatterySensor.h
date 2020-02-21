#pragma once

#include "BatterySensorInterface.h"
#include "BatteryInterface.h"

class BatterySensor : public BatterySensorInterface
{
public:
	BatterySensor(BatteryInterface* batteryIf);
	int stepsLeft() const;
private:
	BatteryInterface* m_batteryIf;
};

