#pragma once
#include <iostream>
#include <fstream>

#include "..\Common\Common.h"
namespace simulation
{
	class HouseInterface
	{
	public:
		virtual bool isClean() const = 0;
		virtual bool isWall(common::Direction d) const = 0;
		virtual bool isDirty() const = 0;
		//virtual void moveRobot(common::Direction d)=0;
		virtual float getCleanPercentage() const = 0;  // finalTotalDirtAmount / originalTotalDirtAmount 
		virtual uint32_t getMaxSteps() const = 0;
		virtual common::Direction updateLastStep(common::Direction d) = 0;
		virtual bool isOnDockingLocation() const = 0;
		virtual void printHouse(std::ostream& resultfile) const = 0;


	};

}