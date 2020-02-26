#include "CellInfo.h"

using namespace robotalgo;

CellInfo::CellInfo(bool isClean, bool stepToDocking, bool isWall)
{
	m_isClean = isClean;
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