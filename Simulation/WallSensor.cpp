#include "WallSensor.h"

using namespace simulation;

//k1 WallSensor::WallSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
WallSensor::WallSensor(House* houseIf) : m_houseIf(houseIf)
{}

bool WallSensor::isWall(common::Direction d) const
{
	return m_houseIf->isWall(d);
}