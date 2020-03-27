#include "CellInfo.h"

using namespace robotalgo;

CellInfo::CellInfo(uint32_t stepToDocking, bool isWall)
{
	m_isDirty = true;
	m_stepsToDocking = stepToDocking;
	m_isWall = isWall;
}

void CellInfo::visitCell()
{
	m_visited = true;
}

bool CellInfo::isVistedCell() const
{
	return m_visited;
}

uint32_t CellInfo::getStepsToDocking() const
{
	return m_stepsToDocking;
}

void CellInfo::updatePathToDocking(CellInfo* neighbour)
{
	if (neighbour->m_stepsToDocking < (m_stepsToDocking - 1))
	{
		m_stepsToDocking = neighbour->m_stepsToDocking + 1;
		m_cellToDocking = neighbour;
	}
}

void CellInfo::updateDockingCell() {
	m_stepsToDocking = 0;

	//Probably not needed
	m_isDirty = false;
	bool m_visited = true;
	bool m_isWall = false;
}

