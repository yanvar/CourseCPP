#pragma once
#include "..\Common\Common.h"

#define D_WALL_DISTANCE (0xFFFFFFFE)
#define D_UNINITIALIZED_DISTANCE (0xFFFFFFFF)


namespace robotalgo
{
	class CellInfo
	{
	public:
		CellInfo(uint32_t stepToDocking, bool isWall);
		void visitCell();
		void cleanCell();
		bool isVistedCell() const;
		uint32_t getStepsToDocking() const;
		void setStepsToDocking(uint32_t stepsToDocking);
		//void updatePathToDocking(CellInfo* neighbour);
		//void updatePathToDocking(common::Direction dirToNeighbour); // iterate the whole path includes steps to docking + neighbour directions
		void updateDockingCellInfo();
		bool isDocking();
		bool isWall() const;

	private:
		bool m_isDirty = true;
		//bool m_wasCleaned;
		//class CellInfo* m_cellToDocking = nullptr;  //TODO return direction, not pointer
		//common::Direction m_nextClosestCellToDocking;
		bool m_visited = false;
		bool m_isWall = false;
		// identify cells by distance: Wall = 0xFFFFFFFE, Docking = 0, uninitialized = 0xFFFFFFFF; floore cell distance any ther positive num
		uint32_t m_stepsToDocking = D_UNINITIALIZED_DISTANCE;

		//bool m_isDocking;
		//class CellInfo* m_cellneighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {nullptr};
		//bool m_isWallNeighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {};

	};
};
