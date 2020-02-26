#pragma once

#include "WallsensorInterface.h"
#include "HouseInterface.h"
#include "..\Common\Common.h"

namespace simulation
{

	class WallSensor : public WallSensorInterface
	{
	public:
		WallSensor(HouseInterface* houseIF);
		bool isWall(common::Direction d) const;
	private:
		HouseInterface* m_houseIf;
	};
}