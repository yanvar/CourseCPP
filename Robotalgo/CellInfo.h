#pragma once
#include "..\Common\Common.h"

namespace robotalgo
{
	class CellInfo
	{
	public:
		CellInfo(bool isClean, bool stepToDocking, bool isWall);
		void visitCell();
		bool isVistedCell() const;

	private:
		bool m_isClean;
		bool m_stepsToDocking;
		bool m_visited = false;
		bool m_isWall;
		class CellInfo* m_cellneighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {nullptr};
		bool m_isWallNeighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {};

	};
};
