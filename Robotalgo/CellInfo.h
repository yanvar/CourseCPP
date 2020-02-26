#pragma once
#include "..\Common\Common.h"

namespace robotalgo
{
	class CellInfo
	{
		bool m_isClean;
		bool m_stepToDocking;
		bool m_visted;
		bool m_isWall;
		class CellInfo* m_cellneighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {nullptr};
		bool m_isWallNeighbours[common::Neighbours_INDEX::NEIGHBOURS_TOTAL] = {};
	};
};
