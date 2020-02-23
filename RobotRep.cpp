#include "RobotRep.h"

RobotRep::RobotRep(HouseInterface* house, BatteryInterface* battery) : m_wallSensor(house), m_dirtSensor(house), m_batterySensor(battery)
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

const BatterySensor& RobotRep::getBatterySensor() const
{
     return m_batterySensor;
}
