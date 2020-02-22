#include "RobotRep.h"

//RobotRep::RobotRep(HouseInterface* house, BatteryInterface* battery) : m_wallSensor(house), m_dirtSensor(house), m_batterySensor(battery)
RobotRep::RobotRep(HouseInterface* house) : m_wallSensor(house), m_dirtSensor(house)
{
	
}

 WallSensorInterface* RobotRep::getWallSensor()
{
	return &m_wallSensor;
}

 DirtSensorInterface* RobotRep::getDirtSensor()
 {
	 return &m_dirtSensor;
 }

//BatterySensorInterface* RobotRep::getBatterySensor()
// {
//     return &m_batterySensor;
// }
