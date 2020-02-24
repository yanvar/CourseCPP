#pragma once

#include "Algo.h"
#include <iostream>


class EdgeAlgo : public Algo
{

public:
	EdgeAlgo();
	Direction nextStep(Direction lastMove, bool& finish);
};
