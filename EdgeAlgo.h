#pragma once

#include "RobotAlgorithm.h"
#include <iostream>


class EdgeAlgo : public RobotAlgorithm
{

public:
	EdgeAlgo();
	common::Direction nextStep(common::Direction lastMove, bool& finish);
};
