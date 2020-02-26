#pragma once

#include "WallsensorInterface.h"
//k1 #include "HouseInterface.h"
#include "House.h"
#include "..\Common\Common.h"

namespace simulation
{

	class WallSensor : public WallSensorInterface
	{
	public:
		//k1 WallSensor(HouseInterface* houseIF);
		WallSensor(House* houseIF);
		bool isWall(common::Direction d) const;
	private:
		//k1 HouseInterface* m_houseIf;
		House* m_houseIf;
	};
}