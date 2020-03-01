//#include "HouseMap.h"
//
////using namespace robotalgo;
//namespace robotalgo
//{
//
//	HouseMap::HouseMap()
//	{
//		m_isDirty = true;
//		m_stepsToDocking = stepToDocking;
//		m_isWall = isWall;
//	}
//
//	bool HouseMap::isCellExistsOnMap(std::pair<int, int> coordinates)
//	{
//		auto it = m_houseMap.find(m_robotCurLocation);
//		if (it == m_mapCells.end())
//			return false;
//		return true;
//	}
//
//
//	//Adds new cell
//	int HouseMap::addNewCellToMap(std::pair<int, int> coordinates, bool isWall, int stepsToDocking = -1)
//	{
//		auto it = m_houseMap.find(m_robotCurLocation);
//		if (it == m_mapCells.end()) 
//		{
//			//Aloc new cell info and add to map
//			CellInfo* info = new CellInfo(stepsToDocking, isWall);
//			m_mapCells.insert(MapCellType(coordinates, info));
//			return 0;
//		}
//		else
//		{
//			cout << "Cell exists!" << std::endl;
//			return 1;
//		}
//	}
//
//	int HouseMap::updateExistingCellOnMap(std::pair<int, int> coordinates, int stepsToDocking = -1)
//	{
//		auto it = m_houseMap.find(m_robotCurLocation);
//		if (it == m_mapCells.end())
//		{
//			//Aloc new cell info and add to map
//			CellInfo* info = new CellInfo(stepsToDocking, isWall);
//			m_mapCells.insert(MapCellType(coordinates, info));
//			return 0;
//		}
//		else
//		{
//			cout << "Cell exists!" << std::endl;
//			return 1;
//		}
//	}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
