#pragma once
#include "..\Common\Common.h"

namespace robotalgo
{
	class CellInfo
	{
	public:
		CellInfo(uint32_t stepToDocking, bool isWall);
		void visitCell();
		bool isVistedCell() const;
		uint32_t getStepsToDocking() const;
		void updatePathToDocking(CellInfo *neighbour);
		void updateDockingCell();


	private:
		bool m_isDirty;
		uint32_t m_stepsToDocking;
		class CellInfo* m_cellToDocking = nullptr;
		bool m_visited = false;
		bool m_isWall;
		//class CellInfo* m_cellneighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {nullptr};
		//bool m_isWallNeighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {};

	};
};
