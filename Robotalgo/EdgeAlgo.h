#pragma once

#include "RobotAlgorithm.h"
#include <iostream>

namespace robotalgo
{

	class EdgeAlgo : public robotalgo::RobotAlgorithm
	{

	public:
		EdgeAlgo();
		common::Direction nextStep(common::Direction lastMove, bool& finish);
		virtual const std::string& getName() const override;
		virtual const std::string& getDescription() const override;

		common::Direction calcNextStep(common::State robotState, common::Direction lastMove); //actually robot State is accessible
		common::Direction calcNextCleanCleanStep();
		common::Direction calcNextCleanMoveStep(common::Direction lastMove);
		common::Direction calcNextReturnStep();
		common::Direction calcNextDockStep();
		common::Direction calcNextFinishStep();
	};
}
