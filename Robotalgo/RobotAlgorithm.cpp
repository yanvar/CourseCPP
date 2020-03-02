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

//Return cell if exist or nullptr otherwise
//CellInfo* RobotAlgorithm::getCellInfoByLocation(std::pair<int, int> location)
//{
//	auto it = m_mapCells.find(location);
//	if (it == m_mapCells.end())
//		return nullptr;
//
//	return it->second;
//}

//Return distance to Docking if cell exists or maxDistance = 0xFFFFFFFF
uint32_t RobotAlgorithm::getCellDistanceToDByLocation(std::pair<int, int> location)
{
	auto it = m_mapCells.find(location);
	if (it == m_mapCells.end())
		return D_UNINITIALIZED_DISTANCE;

	return it->second->getStepsToDocking();
}

uint32_t RobotAlgorithm::setStepsToDockOnMap(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCell)
{
	// set distance in steps 
	CellInfo* cellToUpdate = findCell(cellCoordinates);
	if ((cellToUpdate == nullptr) || (cellToUpdate->isWall() == true) || (cellToUpdate->isDocking()))
	{
		_ASSERT(!"Function shouldn't try to update distance to D for wall, Docking or unknown cell!");
		return D_MAX_DISTANCE_VAL;
	}
	else
	{
		cellToUpdate->setStepsToDocking(stepsToDfromCell);
		return stepsToDfromCell;
	}
}

//get distance to D from all existing neighbours while standing on specific cell
uint32_t RobotAlgorithm::getMinimumDistanceToDfromAllNeighbours()
{
	uint32_t minNeighboursDistanceToD = D_MAX_DISTANCE_VAL; /// wrong curr location distance shouldn't be part of consideration as i have to add 1 afterwards RobotAlgorithm::distanceToDockingFromLocation(m_robotCurLocation); // D_MAX_INT_VAL; // may start from current value!!
	uint32_t minNeighbourNeighbourDistanceToD = D_MAX_DISTANCE_VAL;
	uint32_t neighbourDistanceToD = D_MAX_DISTANCE_VAL;

	//isCellExistsOnMap(m_robotCurLocation.first)

	// check LEFT neighbour: //k optimize : iter over enum index of Directions
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second));
	//only in case of uninitialized cell it's possible lower neighbours should be checked(flore or Wall shouldn't be tested!)
	//flore - all the neighbours are settled, Wall - we may not pass through it.
	if (neighbourDistanceToD < D_WALL_DISTANCE)
	{
		minNeighboursDistanceToD = neighbourDistanceToD < minNeighboursDistanceToD ? neighbourDistanceToD : minNeighboursDistanceToD;
	}
	else // checks 3 neighbour's neighbours (4th neighbour is currentRobotLocation
	{
		//access LEFT - DOWN
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second - 1));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
		//access LEFT - UP
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second + 1));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
		//access LEFT - LEFT
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 2, m_robotCurLocation.second));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	}
	// check RIGHT neighbour:
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second));
	if (neighbourDistanceToD < D_WALL_DISTANCE)
	{
		minNeighboursDistanceToD = neighbourDistanceToD < minNeighboursDistanceToD ? neighbourDistanceToD : minNeighboursDistanceToD;
	}
	else // checks 3 neighbour's neighbours (4th neighbour is currentRobotLocation
	{
	//access RIGHT - DOWN
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second - 1));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	//access RIGHT - UP
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second + 1));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	//access RIGHT - RIGHT
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 2, m_robotCurLocation.second));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	}
	// check UP neighbour:
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second + 1));
	if (neighbourDistanceToD < D_WALL_DISTANCE)
	{
		minNeighboursDistanceToD = neighbourDistanceToD < minNeighboursDistanceToD ? neighbourDistanceToD : minNeighboursDistanceToD;
	}
	else // checks 3 neighbour's neighbours (4th neighbour is currentRobotLocation
	{
	//access UP - RIGHT
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second + 1));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	//access UP - LEFT
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second + 1));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	//access UP - UP
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second + 2));
	minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	}
	// check DOWN neighbour:
	neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second - 1));
	if (neighbourDistanceToD < D_WALL_DISTANCE)
	{
		minNeighboursDistanceToD = neighbourDistanceToD < minNeighboursDistanceToD ? neighbourDistanceToD : minNeighboursDistanceToD;
	}
	else // checks 3 neighbour's neighbours (4th neighbour is currentRobotLocation
	{
		//access DOWN - LEFT
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first - 1, m_robotCurLocation.second - 1));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
		//access DOWN - RIGHT
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first + 1, m_robotCurLocation.second - 1));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
		//access DOWN - DOWN
		neighbourDistanceToD = getCellDistanceToDByLocation(std::make_pair(m_robotCurLocation.first, m_robotCurLocation.second - 2));
		minNeighbourNeighbourDistanceToD = neighbourDistanceToD < minNeighbourNeighbourDistanceToD ? neighbourDistanceToD : minNeighbourNeighbourDistanceToD;
	}

	if minNeighbourNeighbourDistanceToD < D_WALL_DISTANCE
		minNeighboursDistanceToD = minNeighboursDistanceToD < (minNeighbourNeighbourDistanceToD + 1) ? minNeighboursDistanceToD : (minNeighbourNeighbourDistanceToD + 1);
	
	//we will get at least single initialized (not 0xFFFFFFFF) value, as we come from somewhere.
	return minNeighboursDistanceToD;
}


// check currentLocation - is Dirty + update currentCell
	// check neighbors: all 4 sides
	//       ifExists -
	//          ifWall (thats it)
	//          else isDistanceShouldBeUpdated() // if currentDistance+1 == neighbourDistance (no update needed)
												 // if currentDistance+1 > neighbourDistance  (from current backwards to be updated! recursion)
												 // if currentDistance+1 < neighbourDistance  (from current forward to be updated! recursion)
	//      else - addNewCellToMap
	//			update distance, isClean, isVisited, etc........  onTheWayBack???maybe


void RobotAlgorithm::updateMapping() //include add them to the map or update existing  + set relevant fields
{
	if ((m_robotCurLocation != D_DOCKING_LOCATION)) // usually!?!
	{
		updateCurrentLocationInfo(m_dirtSensor->isDirty());

		//m_DiatanceToDockingFromCurLocation = updateStepsToDock(m_robotCurLocation, getMinimumDistanceToDfromAllNeighbours() + 1);
		// calculate minimal distance to D from all neighbours and set curr location to minimum + 1.
		// it will be starting point to addition of all
		m_DiatanceToDockingFromCurLocation = setStepsToDockOnMap(m_robotCurLocation, getMinimumDistanceToDfromAllNeighbours() + 1);
	}
	
	//k remove maybe: RobotAlgorithm::distanceToDockingFromLocation(m_robotCurLocation);
	//k optimization: replace by iterator over enum Direction!!
	//Check if neighbours exist and if needed, update neighbour accordingly
	//if neighbour isn't exist, add it + check it's neighbours 
	//ONLY ONE!!  iteration over all cells is required as we scaned 2 levels of neighbours and found minimum distance possible
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




bool RobotAlgorithm::addNewCell(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCurrentLocation, bool isCellWall)
{
	auto it = m_mapCells.find(cellCoordinates);
	if (it == m_mapCells.end()) {
		CellInfo* cell = new CellInfo(stepsToDfromCurrentLocation, isCellWall);
		m_mapCells.insert(MapCellType(cellCoordinates, cell));
		return true;
	}
	cout << "Cell exists" << std::endl;
	return false;
	
}

bool RobotAlgorithm::isCellExistsOnMap(std::pair<int, int> coordinates)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end())
		return false;
	return true;
}


//MAP APIs

void RobotAlgorithm::updateCurrentLocationInfo(bool isDirty)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end())
		_ASSERT(!"ERROR! Cell isn't on the map! Can't update isDirty.");
		
	it->second->visitCell();
	if (!isDirty)
		it->second->cleanCell();
}

//Add newCell if not exists. Update in case distance should be updated
//bool RobotAlgorithm::addNeighbourToMap(Direction NeighborLocationSide)
CellInfo* RobotAlgorithm::addNeighbourToMap(std::pair<int, int> neighbourCoordinates, Direction NeighborLocationSide, uint32_t stepsToDfromCurrentLocation)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it == m_mapCells.end())  //cell doesn't exist
	{
		//Aloc new cell info and add to map
		CellInfo* cell = new CellInfo(stepsToDfromCurrentLocation + 1, m_wallSensor->isWall(NeighborLocationSide));
		m_mapCells.insert(MapCellType(m_robotCurLocation, cell));
		return cell;
	}

	// in case neighbour is already exists on Map
	uint32_t stepsToDfromNeighbour = it->second->getStepsToDocking();
	if ((stepsToDfromNeighbour == stepsToDfromCurrentLocation + 1) || (stepsToDfromNeighbour == stepsToDfromCurrentLocation - 1))
	{
		cout << "Neighbour exists on map. Its steps to Docking shouldn't be updated!" << std::endl;
	}
	else if (stepsToDfromNeighbour < stepsToDfromCurrentLocation - 1)
	{
		cout << "Neighbour exists on map. Steps from Current Location should be updated!" << std::endl;
		updateStepsToDock(m_robotCurLocation, stepsToDfromNeighbour + 1);
	}
	else //if (stepsToDfromNeighbour > stepsToDfromCurrentLocation + 1)
	{
		cout << "Neighbour exists on map. Steps from Neighbour Location should be updated!" << std::endl;
		updateStepsToDock(neighbourCoordinates, stepsToDfromCurrentLocation + 1);
	}
	return it->second;
}

CellInfo* RobotAlgorithm::findCell(std::pair<int, int> neighbourCoordinates)
{
	auto it = m_mapCells.find(m_robotCurLocation);
	if (it != m_mapCells.end())
		return it->second;
	return nullptr;
}

uint32_t RobotAlgorithm::distanceToDockingFromLocation(std::pair<int, int> cellCoordinates)
{
	auto it = m_mapCells.find(cellCoordinates);
	if (it == m_mapCells.end())
		return 0xFFFFFFFF;
	return it->second->getStepsToDocking();
}

void RobotAlgorithm::updateDistanceForSingleDirection(std::pair<int, int> neighbourCoordinates, uint32_t stepsToDfromCell)
{
	//uint32_t neighbourDistanceToDocking = distanceToDockingFromLocation(std::make_pair(cellCoordinates.first - 1, cellCoordinates.second));
	uint32_t neighbourDistanceToDocking = RobotAlgorithm::distanceToDockingFromLocation(neighbourCoordinates);
	if ((neighbourDistanceToDocking == 0) || (neighbourDistanceToDocking == 0xFFFFFFFF))
		return;

	int distanceToNeighbour = neighbourDistanceToDocking - stepsToDfromCell;
	if ((abs(distanceToNeighbour)) == 1)
	return;// finished update in this direction     //// , Direction::LEFT, m_DiatanceToDockingLocation);
	else if (distanceToNeighbour > 1) // neighbour is further from D, then currentCell (it should be decremented to dist + 1
	{
		RobotAlgorithm::updateStepsToDock(neighbourCoordinates, stepsToDfromCell - 1); //LEFT
		return;
	}
	else //distance to neighbour < - 1  //SHOULDN"T HAPPEN as before update all consecutive cells are on 1 distance!!! ERROR!
		_ASSERT(!"ERROR! Nighbour distance to D is smaller than current cell");
}

// gets location to update + value to set
// during update, values are DECREMENTED ONLY, while direction of change may differ
// direction is decided on the 1st encounter with already known cell (either current or neighbour.
// This function already knows that specific cell should be updated, while neghbours may require update as well
void RobotAlgorithm::updateStepsToDock(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCell)
{
	//uint32_t neighbourDistanceToDocking;
	// set distance in steps 
	CellInfo* cellToUpdate = findCell(cellCoordinates);
	if ((cellToUpdate == nullptr) || (cellToUpdate->isWall() == true) || (cellToUpdate->isDocking()))
	{
		_ASSERT(!"Function shouldn't try to update distance to D for wall, Docking or unknown cell!");
	}
		
	// in case cell is floor
	cellToUpdate->setStepsToDocking(stepsToDfromCell);

	//check all 4 neighbours, in case of not existOnMap, Wall or val  == +/-1 return
	//check LEFT + rest of directions
	updateDistanceForSingleDirection(std::make_pair(cellCoordinates.first - 1, cellCoordinates.second), stepsToDfromCell);
	updateDistanceForSingleDirection(std::make_pair(cellCoordinates.first + 1, cellCoordinates.second), stepsToDfromCell);
	updateDistanceForSingleDirection(std::make_pair(cellCoordinates.first, cellCoordinates.second - 1), stepsToDfromCell);
	updateDistanceForSingleDirection(std::make_pair(cellCoordinates.first, cellCoordinates.second + 1), stepsToDfromCell);

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



//uint32_t RobotAlgorithm::checkNeighbourDistanceToD(std::pair<int, int> NeighbourCoordinates, currentCellDistance)
//{
//
//}
