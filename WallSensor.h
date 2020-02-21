#pragma once

#include "WallSensorInterface.h"
#include "HouseInterface.h"

class WallSensor : public WallSensorInterface
{
public:
	WallSensor(HouseInterface* houseIf);
	bool isWall(Direction d) const;
private:
	HouseInterface* m_houseIf;
};
