#include "DirtSensor.h"

using namespace simulation;

//DirtSensor::DirtSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
DirtSensor::DirtSensor(House* houseIf) : m_houseIf(houseIf)
{}

bool DirtSensor::isDirty() const
{
	return m_houseIf->isDirty();
}