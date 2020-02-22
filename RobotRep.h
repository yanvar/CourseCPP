#pragma once
#include "HouseInterface.h"
#include "WallSensor.h"
#include "DirtSensor.h"
#include "BatterySensor.h"
#include "BatterySensorInterface.h"
#include "BatteryInterface.h"
#include "House.h"
#include "Battery.h"

class RobotRep
{

public:
	//RobotRep(HouseInterface* house, BatteryInterface* battery);
	RobotRep(HouseInterface* house/*, BatteryInterface* battery*/);

	//TODO: implement all virtual functions of houseIF!

	 WallSensorInterface* getWallSensor();
	 DirtSensorInterface* getDirtSensor();
	 //BatterySensorInterface* getBatterySensor();
private:
	WallSensor m_wallSensor;
	DirtSensor m_dirtSensor;
	//BatterySensor m_batterySensor;
};




