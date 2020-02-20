#pragma once
#include "HouseInterface.h"
#include "House.h"
#include "Battery.h"

class RobotRep
{

public:
	RobotRep(House house, Battery battery);

	//implement all virtual functions of houseIF!

	// TODO: add 3 functions + implement (call House API)

	bool isWall(Direction d) const;
	bool isDirty() const;
	int stepsLeft() const;

private:
	House m_houseInstance;
	Battery m_battery;
	
};




