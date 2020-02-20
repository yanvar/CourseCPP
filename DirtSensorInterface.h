#pragma once

#include "Common.h"

class DirtSensorInterface
{
public:
	virtual bool isDirty() const = 0;
};
