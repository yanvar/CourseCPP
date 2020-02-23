#include "RobotRep.h"

//RobotRep::RobotRep(HouseInterface* house, BatteryInterface* battery) : m_wallSensor(house), m_dirtSensor(house), m_batterySensor(battery)
RobotRep::RobotRep(HouseInterface* house) : m_wallSensor(house), m_dirtSensor(house)
{
	
}

const WallSensor& RobotRep::getWallSensor() const
{
	return m_wallSensor;
}

const DirtSensor& RobotRep::getDirtSensor() const
 {
	 return m_dirtSensor;
 }

//BatterySensorInterface* RobotRep::getBatterySensor()
// {
//     return &m_batterySensor;
// }
