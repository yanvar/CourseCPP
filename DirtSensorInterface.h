#pragma once

#include "Common\Common.h"

class DirtSensorInterface
{
public:
	virtual bool isDirty() const = 0;
};
