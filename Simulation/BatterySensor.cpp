#include "BatterySensor.h"

using namespace simulation;

//k1 BatterySensor::BatterySensor(BatteryInterface* batteryIf) : m_batteryIf(batteryIf)
BatterySensor::BatterySensor(Battery* battery) : m_battery(battery)
{}

int BatterySensor::stepsLeft() const
{
	//k1 return m_batteryIf->stepsLeft();
	return m_battery->stepsLeft();
}