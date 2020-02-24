#pragma once
#include "HouseInterface.h"
#include "WallSensor.h"
#include "DirtSensor.h"
#include "BatterySensor.h"
#include "BatterySensorInterface.h"
#include "BatteryInterface.h"
#include "House.h"
#include "Battery.h"

class RobotRepImpl
{

public:
	RobotRepImpl(HouseInterface* house, BatteryInterface* battery);

	 const WallSensor& getWallSensor() const;
	 const DirtSensor& getDirtSensor() const;
	 const BatterySensor& getBatterySensor() const;

private:
	WallSensor m_wallSensor;
	DirtSensor m_dirtSensor;
	BatterySensor m_batterySensor;
};




