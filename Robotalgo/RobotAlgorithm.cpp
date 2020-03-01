#include "RobotAlgorithm.h"
#include <cassert>

using namespace std;
using namespace common;
using namespace robotalgo;


RobotAlgorithm::RobotAlgorithm()
{
	std::cout << "ALGO: Constructor: Base class object - Algo was created!" << std::endl;
	/*CellInfo* current = getCellInfoByLocation(m_robotCurLocation, Direction::STAY);
	current->updateDockingCell();*/
	RobotAlgorithm::addNewCell(D_DOCKING_LOCATION, 0, false);
	m_robotCurLocation = D_DOCKING_LOCATION;
	m_DiatanceToDockingFromCurLocation = 0;
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
State RobotAlgorithm::updateState()
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

void RobotAlgorithm::updateMapping() //include add them to the map or update existing  + set relevant fields
{
	// check currentLocation - is Dirty + update currentCell
	// check neighbors: all 4 sides
	//       ifExists -
	//          ifWall (thats it)
	//          else isDistanceShouldBeUpdated() // if currentDistance+1 == neighbourDistance (no update needed)
	                                             // if currentDistance+1 > neighbourDistance  (from current backwards to be updated! recursion)
												 // if currentDistance+1 < neighbourDistance  (from current forward to be updated! recursion)
	//      else - addNewCellToMap
	//			update distance, isClean, isVisited, etc........  onTheWayBack???maybe
											
	//if  

	//m_isCurrentLocationDirty = m_dirtSensor->isDirty(); //should be part of the mapping update!
	updateCurrentLocationInfo(m_dirtSensor->isDirty());
	//replace by iterator over enum Direction!!
	m_DiatanceToDockingFromCurLocation = RobotAlgorithm::distanceToDockingFromLocation(m_robotCurLocation);

	//Check if neighbours exist and update accordingly 
	RobotAlgorithm::addNeighbourToMap(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second), Direction::LEFT, m_DiatanceToDockingFromCurLocation);
	//k mange neighbors amount current->updatePathToDocking(neighbors);
	RobotAlgorithm::addNeighbourToMap(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second + 1), Direction::UP, m_DiatanceToDockingFromCurLocation);
	//k mange neighbors amount current->updatePathToDocking(neighbors);
	RobotAlgorithm::addNeighbourToMap(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second), Direction::RIGHT, m_DiatanceToDockingFromCurLocation);
	//k mange neighbors amountcurrent->updatePathToDocking(neighbors);
	RobotAlgorithm::addNeighbourToMap(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second - 1), Direction::DOWN, m_DiatanceToDockingFromCurLocation);
	//k mange neighbors amountcurrent->updatePathToDocking(neighbors);
	




	//CellInfo* current = getCellInfoByLocation(m_robotCurLocation, Direction::STAY);

	////Check if neighbours exist and update accordingly 
	//CellInfo*  neighbors = getCellInfoByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second), Direction::LEFT);
	//current->updatePathToDocking(neighbors);
	//getCellInfoByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second + 1), Direction::UP);
	//current->updatePathToDocking(neighbors);
	//getCellInfoByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second), Direction::RIGHT);
	//current->updatePathToDocking(neighbors);
	//getCellInfoByLocation(std::make_pair(m_robotCurLocation.first , m_robotCurLocation.second -1), Direction::DOWN);
	//current->updatePathToDocking(neighbors);
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

//std::pair<int,int> RobotAlgorithm::getNeighbourCoordinates(Direction neighbourDirection, /*std::pair<int, int> currentLocation*/)
//{
//	std::pair<int, int> neighbourCoordinates = m_robotCurLocation;
//
//	switch (neighbourDirection)
//	{
//	case(Direction::LEFT):
//		neighbourCoordinates.first -= 1;
//		break;
//	case(Direction::RIGHT):
//		neighbourCoordinates.first += 1;
//		break;
//	case(Direction::UP):
//		neighbourCoordinates.second += 1;
//		break;
//	case(Direction::DOWN):
//		neighbourCoordinates.second -= 1;
//		break;
//
//	default:
//		break;
//	}
//
//	return neighbourCoordinates;
//}




bool RobotAlgorithm::addNewCell(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCurrentLocation, bool isWall)
{
	//Return cell if exist and if not insert to map
	CellInfo* getCellInfoByLocation(std::pair<int, int> location, Direction d)
	{
		auto it = m_mapCells.find(m_robotCurLocation);
		if (it == m_mapCells.end()) {
			CellInfo* cell = new CellInfo(stepsToDfromCurrentLocation, isWall);
			m_mapCells.insert(MapCellType(cellCoordinates, cell));
			return true;
		}
		cout << "Cell exists";
		return false;
	}
}

bool RobotAlgorithm::isCellExist()
{
	return true;
}


//MAP APIs

void RobotAlgorithm::updateCurrentLocationInfo(bool isDirty)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end())
		_ASSERT();
		
	it.visitCell();
	if (!isDirty)
		it.cleanCell();
}

//Add newCell if not exists. Update in case distance should be updated
//bool RobotAlgorithm::addNeighbourToMap(Direction NeighborLocationSide)
CellInfo* RobotAlgorithm::addNeighbourToMap(std::pair<int, int> neighbourCoordinates, Direction NeighborLocationSide, uint32_t stepsToDfromCurrentLocation)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end())  //cell doesn't exist
	{
		//Aloc new cell info and add to map
		CellInfo* cell = new CellInfo(stepsToD + 1, m_wallSensor->isWall(NeighborLocationSide));
		m_mapCells.insert(MapCellType(m_robotCurLocation, cell));
		return cell;
	}
	int stepsToDfromNeighbour = it->getStepsToDocking();
	//if !((stepsToDfromNeighbour = stepsToDfromCurrentLocation + 1) || (stepsToDfromNeighbour = stepsToDfromCurrentLocation - 1))
	if ((stepsToDfromNeighbour == stepsToDfromCurrentLocation + 1) || (stepsToDfromNeighbour == stepsToDfromCurrentLocation - 1))
	{
		cout << "Neighbour exists on map. Its steps to Docking shouldn't be updated!"
	}
	else if (stepsToDfromNeighbour < stepsToDfromCurrentLocation - 1)
	{
		cout << "Neighbour exists on map. Steps from Current Location should be updated!"
		updateStepsToDock(m_currentRobotLocation, stepsToDfromNeighbour + 1);
	}
	else //if (stepsToDfromNeighbour > stepsToDfromCurrentLocation + 1)
	{
		cout << "Neighbour exists on map. Steps from Neighbour Location should be updated!"
		updateStepsToDock(neighbourCoordinates, stepsToDfromCurrentLocation + 1);
	}
	return it->second;
}

CellInfo* RobotAlgorithm::findCell(std::pair<int, int> neighbourCoordinates)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it != m_mapCells.end())
		return it;
	}
return nullptr;

uint32_t RobotAlgorithm::distanceToDockingFromLocation(std::pair<int, int> cellCoordinates)
{
	auto it = m_mapCells.find(cellCoordinates);
	if (it == m_mapCells.end())
		return 0xFFFFFFFF;
	return it->getStepsToDocking();
}

// gets location to update + value to set
// during update, values are DECREMENTED ONLY, while direction of change may differ
// direction is decided on the 1st encounter with already known cell (either current or neighbour.
// This function already knows that specific cell should be updated, while neghbours may require update as well
void RobotAlgorithm::updateStepsToDock(std::pair<int, int> cellCoordinates, stepsToDfromCell)
{
	uint32_t neighbourDistanceToDocking;
	// set distance in steps 
	CellInfo* cellToUpdate = findCell(cellCoordinates);
	if ((cellToUdate == nullptr) || (cellToUdate->isWall() == true) || (cellToUdate->isDocking())
	{
		ASSERT(!"Function shouldn't try to update distance to D for wall, Docking or unknown cell!")
		return;
	}
		
	// in case cell is floor
	cellToUpdate->setStepsToDocking(stepsToDfromCell);

	//check all 4 neighbours, in case of not existOnMap, Wall or val  == +/-1 return
	//check LEFT + rest of directions
	updateDistanceForSingleDirection((std::make_pair(cellCoordinates.first - 1, cellCoordinates.second), stepsToDfromCell);
	updateDistanceForSingleDirection((std::make_pair(cellCoordinates.first + 1, cellCoordinates.second), stepsToDfromCell);
	updateDistanceForSingleDirection((std::make_pair(cellCoordinates.first, cellCoordinates.second - 1), stepsToDfromCell);
	updateDistanceForSingleDirection((std::make_pair(cellCoordinates.first, cellCoordinates.second + 1), stepsToDfromCell);

	//neighbourDistanceToDocking = distanceToDockingFromLocation(std::make_pair(cellCoordinates.first - 1, cellCoordinates.second));
	//if ((neighbourDistanceToDocking == 0) || (neighbourDistanceToDocking == 0xFFFFFFFF))
	//	return;

	//int distanceToNeighbour = neighbourDistanceToDocking - stepsToDfromCell;
	//if (abs(distanceToNeighbour)) == 1) 
	//	return;// finished update in this direction     //// , Direction::LEFT, m_DiatanceToDockingLocation);
	//else if  distanceToNeighbour >  1 // neighbour is further from D, then currentCell (it should be decremented to dist + 1
	//{	
	//	updateStepsToDock(std::make_pair(cellCoordinates.first - 1, cellCoordinates.second), stepsToDfromCell - 1); //LEFT
	//	return;
	//}
	//else //distance to neighbour < - 1  //SHOULDN"T HAPPEN as before update all consecutive cells are on 1 distance!!! ERROR!
	//	ASSERT(!"ERROR!")
	//
	//	/*updateStepsToDock(m_currentRobotLocation, stepsToDfromNeighbour + 1)
	//	check neighbour Right
	//	if neighbourSteps == current + 1 or current - 1
	//		return; STOP!!
	//	else updateStepsToDock(m_currentRobotLocation, stepsToDfromNeighbour + 1)*/
	//		3



	//		4

}

void RobotAlgorithm::updateDistanceForSingleDirection(std::pair<int, int> NeighbourCoordinates, stepsToDfromCell)
{
	//uint32_t neighbourDistanceToDocking = distanceToDockingFromLocation(std::make_pair(cellCoordinates.first - 1, cellCoordinates.second));
	uint32_t neighbourDistanceToDocking = RobotAlgorithm::distanceToDockingFromLocation(NeighbourCoordinates));
	if ((neighbourDistanceToDocking == 0) || (neighbourDistanceToDocking == 0xFFFFFFFF))
		return;

	int distanceToNeighbour = neighbourDistanceToDocking - stepsToDfromCell;
	if (abs(distanceToNeighbour)) == 1)
	return;// finished update in this direction     //// , Direction::LEFT, m_DiatanceToDockingLocation);
	else if  distanceToNeighbour > 1 // neighbour is further from D, then currentCell (it should be decremented to dist + 1
	{
		RobotAlgorithm::updateStepsToDock(NeighbourCoordinates, stepsToDfromCell - 1); //LEFT
		return;
	}
	else //distance to neighbour < - 1  //SHOULDN"T HAPPEN as before update all consecutive cells are on 1 distance!!! ERROR!
		ASSERT(!"ERROR! Nighbour distance to D is smaller than current cell")
}

uint32_t RobotAlgorithm::checkNeighbourDistanceToD(std::pair<int, int> NeighbourCoordinates, currentCellDistance)
{

}
