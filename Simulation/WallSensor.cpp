#include "WallSensor.h"

using namespace simulation;

WallSensor::WallSensor(HouseInterface* houseIf) : m_houseIf(houseIf)
{}

bool WallSensor::isWall(common::Direction d) const
{
	return m_houseIf->isWall(d);
}