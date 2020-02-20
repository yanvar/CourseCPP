#include "RobotRep.h"

//RobotRep::RobotRep(HouseInterface* house, Battery battery) : m_wallSensor(house)
RobotRep::RobotRep(HouseInterface* house) : m_wallSensor(house), m_dirtSensor(house)
{
	
}

 WallSensor* RobotRep::getWallSensor()
{
	return &m_wallSensor;
}

 DirtSensor* RobotRep::getDirtSensor()
 {
	 return &m_dirtSensor;
 }


/*
bool RobotRep::isWall(Direction d) const
{
	return m_houseInstance.isWall(d);
}



int RobotRep::stepsLeft() const
{
	return m_battery.getBatteryLevelInSteps();
}

*/
