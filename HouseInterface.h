#pragma once
#include <iostream>

#include "Common.h"
class HouseInterface
{
public:
	virtual bool isClean() const=0;
	virtual bool isWall(Direction d) const =0;
	virtual bool isDirty() const =0;
	virtual void moveRobot(Direction d)=0;
	virtual float getCleanPercentage() const = 0;  // finalTotalDirtAmount / originalTotalDirtAmount 
	virtual uint32_t getMaxSteps() const = 0;
	virtual Direction updateLastStep(Direction d) = 0;
	virtual bool isOnDockingLocation() const = 0;

};

