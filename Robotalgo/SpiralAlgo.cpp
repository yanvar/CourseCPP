#include "SpiralAlgo.h"

using namespace common;

namespace robotalgo
{
	SpiralAlgo::SpiralAlgo()
	{
		std::cout << "SpiralALGO: Constructor: Base class object - SpiralAlgo was created!" << std::endl;
		m_algoName = "SpiralAlgo";
		m_algoDescription = "Goes in spiral around the center";
	}

	Direction SpiralAlgo::nextStep(Direction lastMove, bool& finish)
	{
		return Direction::STAY;
	}

	const std::string& SpiralAlgo::getName() const
	{
		return m_algoName;
	}
	const std::string& SpiralAlgo::getDescription() const
	{
		return m_algoDescription;
	}
}

