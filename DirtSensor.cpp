#include "DirtSensor.h"

DirtSensor::DirtSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
{}

bool DirtSensor::isDirty() const
{
	return m_houseIf->isDirty();
}