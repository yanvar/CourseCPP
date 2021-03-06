#pragma once

#include "RobotAlgorithm.h"
#include <iostream>

namespace robotalgo
{

	class SpiralAlgo : public robotalgo::RobotAlgorithm
	{

	public:
		SpiralAlgo();
		common::Direction nextStep(common::Direction lastMove, bool& finish);

		virtual const std::string& getName() const override;
		virtual const std::string& getDescription() const override;

	};
}