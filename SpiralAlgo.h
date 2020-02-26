#pragma once

#include "RobotAlgorithm.h"
#include <iostream>


class SpiralAlgo : public RobotAlgorithm
{

public:
	SpiralAlgo();
	common::Direction nextStep(common::Direction lastMove, bool& finish);

};