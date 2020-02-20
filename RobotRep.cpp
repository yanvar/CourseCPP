#include "RobotRep.h"

RobotRep::RobotRep(House house, Battery battery) : m_houseInstance(house), m_battery(battery)
{
	
}

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
