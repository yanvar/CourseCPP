#include "RobotRepImpl.h"

RobotRepImpl::RobotRepImpl(HouseInterface* house, BatteryInterface* battery) : m_wallSensor(house), m_dirtSensor(house), m_batterySensor(battery) //k ??? how battery sensor type m_batterySensor initialized by BatteryInterface*
{
}

const WallSensor& RobotRepImpl::getWallSensor() const
{
	return m_wallSensor;
}

const DirtSensor& RobotRepImpl::getDirtSensor() const
 {
	 return m_dirtSensor;
 }

const BatterySensor& RobotRepImpl::getBatterySensor() const
{
     return m_batterySensor; //k  ??? how m_batterySensor type m_batterySensor, returns const BatterySensor& 
}
