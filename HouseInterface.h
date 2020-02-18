#pragma once
#include "Common.h"
class HouseInterface
{
public:
	virtual bool isClean() const=0;
	virtual bool isWall(Direction d) const =0;
	virtual bool isDirty() const =0;
	virtual void moveRobot(Direction d)=0;

};

