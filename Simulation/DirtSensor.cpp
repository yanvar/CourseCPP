#include "DirtSensor.h"

using namespace simulation;

//DirtSensor::DirtSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
DirtSensor::DirtSensor(House* house) : m_house(house)
{}

bool DirtSensor::isDirty() const
{
	//k1 return m_houseIf->isDirty();
	return m_house->isDirty();
}