#include "RobotAlgorithm.h"
#include <cassert>

using namespace std;
using namespace common;
using namespace robotalgo;


RobotAlgorithm::RobotAlgorithm()
{
	std::cout << "ALGO: Constructor: Base class object - Algo was created!" << std::endl;
	CellInfo* current = getCellInfoByLocation(m_robotCurLocation, Direction::STAY);
	current->updateDockingCell();
}

const uint32_t RobotAlgorithm::getRemainingSteps()
{
	return m_remainingSteps;
}


void RobotAlgorithm::decrementRemainingStep()
{
	m_remainingSteps--;
}

uint32_t RobotAlgorithm::calculateOptimalStepsToCharge()
{
	return 0;
}


uint32_t RobotAlgorithm::calculateChargeRateAndStore()
{
	return 0;
}

// decide whether we on GO, RETURN or CHARGE state
// current implementation assumption - batteryConsumptionRate == 1 !!!!!!!!!!!!!!!!
State RobotAlgorithm::calculateState()
{
	// minimum between battery and configuration steps left affects decision
	int bateryStepsLeft = m_batterySensor->stepsLeft();
	int stepsLeftToReturn = (uint32_t)bateryStepsLeft < m_remainingSteps ? bateryStepsLeft : m_remainingSteps;
	int stepsFromDockingToGetAndReturnFromClosestDirtSquare = 1;
	// optimization; int stepsToClosestSquareToVisit = calcStepsToClosestSquareToVisit();
	// optimization; pair<int, int> closestSquareToVisitCoordinates = getCoordinatesClosestSquareToVisit();

	switch (m_robotState)
	{
	case(State::CLEAN_CLEAN):
		if (m_houseIsClean)
			return State::RETURN;
		if ((m_shortestPathToD + m_spareSteps) == stepsLeftToReturn)
			return State::RETURN;
		if (m_isCurrentLocationDirty)
			return State::CLEAN_CLEAN;

		//where to move
		// optimization; if m_stepsToClosestDirtySquare + getDistToDockFromSquare
		// optim: m_locationToMoveCoordinates = recursiveScanForNextMoveLocation(m_locationToMoveDirectionsVector);
		return State::CLEAN_MOVE;

	case(State::CLEAN_MOVE):
		if ((m_shortestPathToD + m_spareSteps) == stepsLeftToReturn)
			return State::RETURN;
		return State::CLEAN_MOVE;

	case(State::RETURN):
		if (m_robotCurLocation == D_DOCKING_LOCATION)
			return State::DOCK;
		return State::RETURN;

	case(State::DOCK):	// charge to full or until charged enough to clean some stuff before algoSteps reach ZERO
		stepsFromDockingToGetAndReturnFromClosestDirtSquare = (m_distanceToClosestNotCleanSquare + m_spareSteps) * 2 + (uint32_t)(((m_distanceToClosestNotCleanSquare + m_spareSteps) * 2 - bateryStepsLeft) / m_calculatedBatteryChargeRate);
		if (m_remainingSteps < D_BATTERY_MAX_CHARGE)
			if (m_remainingSteps < (uint32_t)stepsFromDockingToGetAndReturnFromClosestDirtSquare) //steps to: charge + forth + back
				return State::FINISH;
			else if (bateryStepsLeft == m_remainingSteps)
					return State::CLEAN_MOVE;
			else
				return State::DOCK;

		else if (bateryStepsLeft == D_BATTERY_MAX_CHARGE) //fully charged
				return State::CLEAN_MOVE; //
			 else
				return State::DOCK; // continue charging

	case(State::FINISH):
		return State::FINISH;   //sink state
	default:
		static_assert(1, "Unexpected Robot State!");
		break;
	}
	return State::RETURN;
}

void RobotAlgorithm::updateMapScan(Direction dir)
{
	
}

//Return cell if exist and if not insert to map
CellInfo* RobotAlgorithm::getCellInfoByLocation(std::pair<int, int> location, Direction d)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end()) {
		//Aloc new cell info and add to map
#define STEP_TO_DOCKING_TODO unsigned(-1)
		CellInfo* cell = new CellInfo(STEP_TO_DOCKING_TODO, m_wallSensor->isWall(d));
		m_mapCells.insert(MapCellType(m_robotCurLocation, cell));
		return cell;
	}

	return it->second;
}

void RobotAlgorithm::updateMapping() //include add them to the map or update existing  + set relevand fields
{
	CellInfo* current = getCellInfoByLocation(m_robotCurLocation, Direction::STAY);

	//Check if neighbours exist and update accordingly 
	CellInfo*  neighbors = getCellInfoByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second), Direction::LEFT);
	current->updatePathToDocking(neighbors);
	getCellInfoByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second + 1), Direction::UP);
	current->updatePathToDocking(neighbors);
	getCellInfoByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second), Direction::RIGHT);
	current->updatePathToDocking(neighbors);
	getCellInfoByLocation(std::make_pair(m_robotCurLocation.first , m_robotCurLocation.second -1), Direction::DOWN);
	current->updatePathToDocking(neighbors);
}

void RobotAlgorithm::updateCurrentLocation(Direction lastMove)
{
	switch (lastMove)
	{
	case(Direction::LEFT):
		m_robotCurLocation.first -= 1;
		break;
	case(Direction::RIGHT):
		m_robotCurLocation.first += 1;
		break;
	case(Direction::UP):
		m_robotCurLocation.second += 1;
		break;
	case(Direction::DOWN):
		m_robotCurLocation.second -= 1;
		break;

	default:
		break;
	}
}




bool RobotAlgorithm::addNewCell()
{
	return true;
}

bool RobotAlgorithm::isCellExist()
{
	return true;
}
