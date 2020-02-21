#include "BatterySensor.h"

BatterySensor::BatterySensor(BatteryInterface* batteryIf) : m_batteryIf(batteryIf)
{}

int BatterySensor::stepsLeft() const
{
	return m_batteryIf->stepsLeft();
}