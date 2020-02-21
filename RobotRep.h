#pragma once
#include "HouseInterface.h"
#include "WallSensor.h"
#include "DirtSensor.h"
#include "House.h"
#include "Battery.h"

class RobotRep
{

public:
	RobotRep(HouseInterface* house, Battery battery);
	//RobotRep(HouseInterface* house);

	//implement all virtual functions of houseIF!

	// TODO: add 3 functions + implement (call House API)

	 WallSensor* getWallSensor();
	 DirtSensor* getDirtSensor();
	 Battery* getBattery();
private:
	WallSensor m_wallSensor;
	DirtSensor m_dirtSensor;
	Battery m_battery;

};




