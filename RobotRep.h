#pragma once
#include "HouseInterface.h"
#include "WallSensor.h"
#include "House.h"
#include "Battery.h"

class RobotRep
{

public:
	//RobotRep(HouseInterface* house, Battery battery);
	RobotRep(HouseInterface* house);

	//implement all virtual functions of houseIF!

	// TODO: add 3 functions + implement (call House API)

	 WallSensor* getWallSensor();
private:
	WallSensor m_wallSensor;

/*
	wallSensor = &(robot.getWallSensor());
	dirtSensor = &(robot.getDirtSensor());
	batterySensor = &(robot.getBatterySensor());

	bool isWall(Direction d) const;
	bool isDirty() const;
	int stepsLeft() const;

private:
	HouseInterface* m_houseInstance;
	Battery m_battery;

*/
};




