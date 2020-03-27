#pragma once
#include "..\Common\Common.h"

namespace simulation
{
	class WallSensorInterface
	{
	public:
		virtual bool isWall(common::Direction d) const = 0;
	};
}