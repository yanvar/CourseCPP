#pragma once
#include "Common\Common.h"

class WallSensorInterface
{
public:
	virtual bool isWall(common::Direction d) const = 0;
};
