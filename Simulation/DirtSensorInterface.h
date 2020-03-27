#pragma once

#include "..\Common\Common.h"

namespace simulation
{
	class DirtSensorInterface
	{
	public:
		virtual bool isDirty() const = 0;
	};
}