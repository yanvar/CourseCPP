#pragma once

#include "Common\Common.h"

class BatterySensorInterface
{
public:
	virtual int stepsLeft() const = 0;
};