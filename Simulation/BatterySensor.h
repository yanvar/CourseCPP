#pragma once

//k1 #include "BatteryInterface.h"
#include "Battery.h"
//k1 #include "BatterySensorInterface.h"
#include "BatterySensor.h"
#include "..\Common\Common.h"

namespace simulation
{

	//k1 class BatterySensor : public BatterySensorInterface
	class BatterySensor
	{
	public:
		//k1 BatterySensor(BatteryInterface* batteryIf);
		BatterySensor(Battery* batteryIf);
		int stepsLeft() const;
	private:
		//k1 BatteryInterface* m_batteryIf;
		Battery* m_batteryIf;
	};
}