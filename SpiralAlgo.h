#pragma once

#include "Algo.h"
#include <iostream>


class SpiralAlgo : public Algo
{

public:
	SpiralAlgo();
	Direction nextStep(Direction lastMove, bool& finish);

};