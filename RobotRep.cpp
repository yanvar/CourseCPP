#include "RobotRep.h"

//RobotRep::RobotRep(HouseInterface* house, Battery battery) : m_wallSensor(house)
RobotRep::RobotRep(HouseInterface* house) : m_wallSensor(house)
{
	
}

 WallSensor* RobotRep::getWallSensor()
{
	return &m_wallSensor;
}

/*
bool RobotRep::isWall(Direction d) const
{
	return m_houseInstance.isWall(d);
}

bool RobotRep::isDirty() const
{
	return m_houseInstance.isDirty();
}

int RobotRep::stepsLeft() const
{
	return m_battery.getBatteryLevelInSteps();
}

*/
