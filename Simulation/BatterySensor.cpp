#include "BatterySensor.h"

using namespace simulation;

BatterySensor::BatterySensor(BatteryInterface* batteryIf) : m_batteryIf(batteryIf)
{}

int BatterySensor::stepsLeft() const
{
	return m_batteryIf->stepsLeft();
}