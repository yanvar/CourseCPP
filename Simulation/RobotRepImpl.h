#pragma once
//k1 #include "HouseInterface.h"
#include "House.h"
#include "WallSensor.h"
#include "DirtSensor.h"
#include "BatterySensor.h"
//#include "BatterySensorInterface.h"
//k1 #include "BatteryInterface.h"
//#include "House.h"
#include "Battery.h"

namespace simulation
{

	class RobotRepImpl
	{

	public:
		//k1 RobotRepImpl(HouseInterface* house, BatteryInterface* battery);
		RobotRepImpl(House* house, Battery* battery);

		const WallSensor& getWallSensor() const;
		const DirtSensor& getDirtSensor() const;
		const BatterySensor& getBatterySensor() const;

	private:
		WallSensor m_wallSensor;
		DirtSensor m_dirtSensor;
		BatterySensor m_batterySensor;
	};
}



