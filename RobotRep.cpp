#include "RobotRep.h"

RobotRep::RobotRep(HouseInterface* house, Battery battery) : m_wallSensor(house), m_dirtSensor(house), m_battery(battery)
//RobotRep::RobotRep(HouseInterface* house) : m_wallSensor(house), m_dirtSensor(house)
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

Battery* RobotRep::getBattery()
 {
     return &m_battery;
 }

