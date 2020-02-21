#pragma once

#include "WallsensorInterface.h"
#include "HouseInterface.h"
#include "Common.h"

class WallSensor : public WallSensorInterface
{
public:
	WallSensor(HouseInterface* houseIf);
	bool isWall(Direction d) const;
private:
	HouseInterface* m_houseIf;
};
