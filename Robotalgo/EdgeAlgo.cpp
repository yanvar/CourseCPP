#include "EdgeAlgo.h"

using namespace common;

namespace robotalgo
{

	EdgeAlgo::EdgeAlgo()
	{
		std::cout << "EdgeALGO: Constructor: Base class object - EdgeAlgo was created!" << std::endl;
		m_algoName = "EdgeAlgo";
		m_algoDescription = "Moves towards obstacle and returns";
	}


	Direction EdgeAlgo::nextStep(Direction lastMove, bool& finish)
	{
		Mode robotMode;

		Direction nextStepDirection = Direction::STAY;
		// for testing purposes!
		bool leftSideWall = m_wallSensor->isWall(Direction::LEFT);
		bool rightSideWall = m_wallSensor->isWall(Direction::RIGHT);
		bool downSideWall = m_wallSensor->isWall(Direction::DOWN);
		bool upSideWall = m_wallSensor->isWall(Direction::UP);
		bool isDirty = m_dirtSensor->isDirty();
		int stepsLeft = m_batterySensor->stepsLeft();

		//TODO: next step & Algo! will be implemented next week... 
		updateCurrentLocation(lastMove); // actual location info.
		updateSurroundingMapping(); //no energy required! //based on current location //request 4 direction isWall + isClean on current location
		robotMode = calculateMode(); // BACK if battery level is critical, clean if still have dirt on current location, go to next location based on ALGO in use.
		nextStepDirection = calcNextStep(robotMode);// calc where to go based on mode, Clean ==> STAY, GO - next to clean, BACK - next to Return

	//	cout << "ALGO: nextStep: Next proposed step is - " << DirectionToStr.at(nextStepDirection) << endl;
		return nextStepDirection;
	}

	const std::string& EdgeAlgo::getName() const
	{
		return m_algoName;
	}
	const std::string& EdgeAlgo::getDescription() const
	{
		return m_algoDescription;
	}
}