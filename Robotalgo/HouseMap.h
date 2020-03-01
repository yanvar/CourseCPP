//#pragma once
//#include "..\Common\Common.h"
//#include "CellInfo.h"
//
//#include <map>
//#include <unordered_map>
//
//
//#define D_DOCKING_LOCATION                std::make_pair(0,0)
//
//namespace robotalgo
//{
//	class HouseMap
//	{
//	public:
//		HouseMap(uint32_t stepToDocking, bool isWall);
//		void visitCell();
//		bool isVistedCell() const;
//		uint32_t getStepsToDocking() const;
//		void setStepsToDocking(uint32_t stepsToDocking);
//		void updatePathToDocking(CellInfo* neighbour);
//		//void updatePathToDocking(common::Direction dirToNeighbour); // iterate the whole path includes steps to docking + neighbour directions
//		void updateDockingCell();
//
//
//	private:
//		struct hash_pair {
//			template <class T1, class T2>
//			size_t operator()(const pair<T1, T2>& p) const
//			{
//				auto hash1 = hash<T1>{}(p.first);
//				auto hash2 = hash<T2>{}(p.second);
//				return hash1 ^ hash2;
//			}
//		};
//
//		typedef std::pair<std::pair<int, int>, CellInfo*> MapCellType;
//		std::unordered_map<std::pair<int, int>, CellInfo*, hash_pair> m_houseMap;
//		std::pair<int, int> m_robotCurrentLocation = D_DOCKING_LOCATION;
//
//
//		//some statistics
//		uint32_t totalCellsCntr = 0;
//		uint32_t totalWallsCntr = 0;
//		uint32_t totalFloorCntr = 0;
//		uint32_t totalCleanedCellsCntr = 0;
//
//		CellInfo* addCellToMap(std::pair<int, int> location, common::Direction neighbourDirection);
//
//		CellInfo* getCellInfoByLocation(std::pair<int, int> location, common::Direction d);
//
//		CellInfo* addCellToMap(std::pair<int, int> location, common::Direction neighbourDirection);
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
//		bool m_isDirty;
//		uint32_t m_stepsToDocking;
//		//class CellInfo* m_cellToDocking = nullptr;  //TODO return direction, not pointer
//		common::Direction m_nextClosestCellToDocking;
//		bool m_visited = false;
//		bool m_isWall;
//		//bool m_isDocking;
//		//class CellInfo* m_cellneighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {nullptr};
//		//bool m_isWallNeighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {};
//
//	};
//};
