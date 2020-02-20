#pragma once

#include "DirtSensorInterface.h"
#include "HouseInterface.h"
#include "Common.h"

class DirtSensor : public DirtSensorInterface
{
public:
	DirtSensor(HouseInterface* houseIf);
	bool isDirty() const;
private:
	HouseInterface* m_houseIf;
};