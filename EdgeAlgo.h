#pragma once

#include "RobotAlgorithm.h"
#include <iostream>


class EdgeAlgo : public RobotAlgorithm
{

public:
	EdgeAlgo();
	Direction nextStep(Direction lastMove, bool& finish);
};
