#include "BatterySensor.h"

using namespace simulation;

//k1 BatterySensor::BatterySensor(BatteryInterface* batteryIf) : m_batteryIf(batteryIf)
BatterySensor::BatterySensor(Battery* batteryIf) : m_batteryIf(batteryIf)
{}

int BatterySensor::stepsLeft() const
{
	return m_batteryIf->stepsLeft();
}