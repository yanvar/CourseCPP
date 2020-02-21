#pragma once

#include "BatterySensorInterface.h"
#include "HouseInterface.h"
#include "Common.h"

class BatterySensor : public BatterySensorInterface
{
public:
	BatterySensor(HouseInterface* houseIf);
	bool isWall(Direction d) const;
private:
	HouseInterface* m_batterySensorIf;
};