#pragma once

#include "DirtSensorInterface.h"
//k1 #include "HouseInterface.h"
#include "House.h"
#include "..\Common\Common.h"

namespace simulation
{
	class DirtSensor : public DirtSensorInterface
	{
	public:
		//k1 DirtSensor(HouseInterface* houseIf);
		DirtSensor(House* house);
		bool isDirty() const;
	private:
		//k1 HouseInterface* m_houseIf;
		House* m_house;
	};
}