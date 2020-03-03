#include "CellInfo.h"

//using namespace robotalgo;
namespace robotalgo
{

	CellInfo::CellInfo(uint32_t stepsToDocking, bool isWall)
	{
		m_isWall = isWall; 
		
		if (m_isWall == false)
		{
			m_stepsToDocking = stepsToDocking;
		}
		////m_isDirty = true; //true until cell is visited nad foundclean
		//m_cellIsClean = false;
		//class CellInfo* m_cellToDocking = nullptr;  //TODO return direction, not pointer
		//common::Direction m_nextClosestCellToDocking;
		////bool m_visited = false;
	}

	void CellInfo::visitCell()
	{
		m_visited = true;
	}

	void CellInfo::cleanCell()
	{
		m_isDirty = false;
	}

	bool CellInfo::isDocking()
	{
		return (m_stepsToDocking == 0);
	}

	bool CellInfo::isVistedCell() const
	{
		return m_visited;
	}

	bool CellInfo::isWall() const
	{
		return m_isWall;
	}

	uint32_t CellInfo::getStepsToDocking() const
	{
		return m_stepsToDocking;
	}

	void robotalgo::CellInfo::setStepsToDocking(uint32_t stepsToDocking)
	{
		m_stepsToDocking = stepsToDocking;
	}

	///void CellInfo::updatePathToDocking(common::Direction dirToNeighbour) //update full path
	/*void updatePathToDocking(CellInfo* neighbour)
	{
		if (neighbour->m_stepsToDocking < (m_stepsToDocking - 1))
		{
			m_stepsToDocking = neighbour->m_stepsToDocking + 1;
			m_nextClosestCellToDocking = neighbour;
		}

	}*/

	void CellInfo::updateDockingCellInfo() {
		m_stepsToDocking = 0;

		//Probably not needed
		m_isDirty = false;
		bool m_visited = true;
		bool m_isWall = false;
	}
}

