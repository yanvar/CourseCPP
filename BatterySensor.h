#pragma once

#include "BatteryInterface.h"
#include "BatterySensorInterface.h"
#include "Common\Common.h"

class BatterySensor : public BatterySensorInterface
{
public:
	BatterySensor(BatteryInterface* batteryIf);
	int stepsLeft() const;
private:
	BatteryInterface* m_batteryIf;
};
