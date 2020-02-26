#pragma once

#include "RobotAlgorithm.h"
#include <iostream>


class SpiralAlgo : public robotalgo::RobotAlgorithm
{

public:
	SpiralAlgo();
	common::Direction nextStep(common::Direction lastMove, bool& finish);

};