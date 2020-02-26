#include "SpiralAlgo.h"

using namespace common;

SpiralAlgo::SpiralAlgo()
{
	std::cout << "SpiralALGO: Constructor: Base class object - SpiralAlgo was created!" << std::endl;
}

Direction SpiralAlgo::nextStep(Direction lastMove, bool& finish)
{
	return Direction::STAY;
}

