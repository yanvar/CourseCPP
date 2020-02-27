#include "EdgeAlgo.h"

using namespace robotalgo;
using namespace common;

//namespace robotalgo
//{

	EdgeAlgo::EdgeAlgo()
	{
		std::cout << "EdgeALGO: Constructor: Base class object - EdgeAlgo was created!" << std::endl;
		m_algoName = "EdgeAlgo";
		m_algoDescription = "Moves towards obstacle and returns";
	}


	Direction EdgeAlgo::nextStep(Direction lastMove, bool& finish)
	{
		Direction nextStepDirection = Direction::STAY;

		//manual testing
		
		//// for testing purposes!
		//bool leftSideWall = m_wallSensor->isWall(Direction::LEFT);
		//bool rightSideWall = m_wallSensor->isWall(Direction::RIGHT);
		//bool downSideWall = m_wallSensor->isWall(Direction::DOWN);
		//bool upSideWall = m_wallSensor->isWall(Direction::UP);
		//bool isDirty = m_dirtSensor->isDirty();
		//int stepsLeft = m_batterySensor->stepsLeft();

		updateCurrentLocation(lastMove); // actual location info.
		m_isCurrentLocationDirty = m_dirtSensor->isDirty();

		updateMapping(); //no energy required! //based on current location //request 4 direction isWall + isClean on current location
		m_robotState = calculateState(); // BACK if battery level is critical, clean if still have dirt on current location, go to next location based on ALGO in use.
		nextStepDirection = calcNextStep(m_robotState, lastMove);// calc where to go based on state, Clean ==> STAY, GO - next to clean, BACK - next to Return

	//	cout << "ALGO: nextStep: Next proposed step is - " << DirectionToStr.at(nextStepDirection) << endl;
		return nextStepDirection;
	}

	Direction EdgeAlgo::calcNextStep(State robotState, Direction lastMove)
	{
		switch (m_robotState)
		{
		case(State::CLEAN_CLEAN):
			return calcNextCleanCleanStep();
			//break;
		case(State::CLEAN_MOVE):
			return calcNextCleanMoveStep(lastMove);
			//break;
		case(State::RETURN):
			return calcNextReturnStep();
			//break;
		case(State::DOCK):
			return calcNextDockStep();
			//break;
		case(State::FINISH):
			return calcNextFinishStep();
			//break;

		default:
			return Direction::STAY;
			//break;
		}
	}

	const std::string& EdgeAlgo::getName() const
	{
		return m_algoName;
	}
	const std::string& EdgeAlgo::getDescription() const
	{
		return m_algoDescription;
	}

	Direction calcNextCleanMoveStep(Direction lastMoveDirection)
	{
		return Direction::STAY;

		//// optim: m_locationToMoveCoordinates = recursiveScanForNextMoveLocation(m_locationToMoveDirectionsVector);
		//switch (lastMoveDirection)
		//{
		//case(Direction::UP):
		//square = getUpperNeighbour(m_robotCurLocation);
		//	if square != WALL && square != CLEANED
		//		return Direction::UP;

		//case(Direction::LEFT):
		//	square = getLeftNeighbour(m_robotCurrentLocation);
		//	if square != WALL && square != CLEANED
		//		return Direction::LEFT;
		//	break;
		//case(Direction::RIGHT):
		//	m_robotCurLocation.first += 1;
		//	break;
		//case(Direction::UP):
		//	m_robotCurLocation.second += 1;
		//	break;
		//case(Direction::DOWN):
		//	m_robotCurLocation.second -= 1;
		//	break;

		//default:
		//	break;
		//
	}

	Direction calcNextCleanCleanStep()
	{
		return Direction::STAY;
	}

	Direction calcNextReturnStep()
	{
	/*	std::pair = map.get_pair.first(m_robotCurLocation);
		return pair.second.closestToDockDirection();*/
		return Direction::STAY;
	}
	
	Direction closestNeighbourToD() // return either cell.dockClosestDirection or scan all neighbours and return one with min distance
	{
		return Direction::STAY;
		//for(auto iter : 
	}

	Direction calcNextDockStep()
	{
		return Direction::STAY;
	}
	Direction calcNextFinishStep()
	{
		//k2 robotalgo::RobotAlgorithm::m_finishFlag = true;
		return Direction::STAY;
	}
	

//}