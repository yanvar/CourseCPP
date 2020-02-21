#pragma once

#include "Common.h"

class BatterySensorInterface
{
public:
	virtual int stepsLeft() const = 0;
};

