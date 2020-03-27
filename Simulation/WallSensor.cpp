#include "WallSensor.h"

using namespace simulation;

//k1 WallSensor::WallSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
WallSensor::WallSensor(House* house) : m_house(house)
{}

bool WallSensor::isWall(common::Direction d) const
{
	//k1 return m_houseIf->isWall(d);
	return m_house->isWall(d);
}