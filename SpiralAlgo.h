#pragma once

#include "RobotAlgorithm.h"
#include <iostream>


class SpiralAlgo : public RobotAlgorithm
{

public:
	SpiralAlgo();
	Direction nextStep(Direction lastMove, bool& finish);

};