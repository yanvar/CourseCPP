#include "Algo.h"

using namespace std;


Algo::Algo()
{
	std::cout << "ALGO: Constructor: Base class object - Algo was created!" << std::endl;
}

//template<class T_RobotRep>
//void Algo::init(T_RobotRep& robot, std::map<std::string, int> config)
//{
//	m_remainingSteps = config["Max_Steps"];
//	m_robotRep = robot;
//}

Direction Algo::nextStep(Direction lastMove, bool& finish)
{
	Direction nextStepDirection = Direction::STAY;
//	bool leftSideWall = m_wallSensor->isWall(Direction::LEFT);
//	bool rightSideWall = m_wallSensor->isWall(Direction::RIGHT);
//	bool downSideWall = m_wallSensor->isWall(Direction::DOWN);
//	bool upSideWall = m_wallSensor->isWall(Direction::UP);
	//bool isClean = m_wallSensor->isWall(Direction::LEFT);

//	cout << "ALGO: nextStep: Next proposed step is - " << DirectionToStr.at(nextStepDirection) << endl;
	return nextStepDirection;
}

const string& Algo::getName() const
{
	return m_algoName;
}


const string& Algo::getDescription() const
{
	return m_algoDescription;
}


const uint32_t Algo::getRemainingSteps()
{
	return m_remainingSteps;
}


void Algo::decrementRemainingStep()
{
	m_remainingSteps--;
}

uint32_t Algo::calculateOptimalStepsToCharge()
{
	return 0;
}


uint32_t Algo::calculateChargeRateAndStore()
{
	return 0;
}

// decide whether we on GO, RETURN or CHARGE mode

Mode Algo::calculateMode()
{
	return Mode::DOCK;
}

void updateMapScan(Direction dir)
{

}
void updateCurrentLocation(Direction dir)
{

}