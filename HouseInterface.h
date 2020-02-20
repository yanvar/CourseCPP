#pragma once
#include "Common.h"
class HouseInterface
{
public:
	virtual bool isClean() const=0;
	virtual bool isWall(Direction d) const =0;
	virtual bool isDirty() const =0;
	virtual void moveRobot(Direction d)=0;
	virtual double getCleanPercentage() const = 0;  // finalTotalDirtAmount / originalTotalDirtAmount 
	virtual int getMaxSteps() const = 0;
	virtual Direction getLastStep(Direction d) const = 0;
	virtual bool isOnDockingLocation() const = 0;

};

