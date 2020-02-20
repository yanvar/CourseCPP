#pragma once
#include "Common.h"

class WallSensorInterface
{
public:
	virtual bool isWall(Direction d) const = 0;
};
