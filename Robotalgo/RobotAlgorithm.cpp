#include "RobotAlgorithm.h"

using namespace std;
using namespace common;
using namespace robotalgo;


RobotAlgorithm::RobotAlgorithm()
{
	std::cout << "ALGO: Constructor: Base class object - Algo was created!" << std::endl;
}

//template should be implemented in .h file
//template<class T_RobotRep>
//void Algo::init(T_RobotRep& robot, std::map<std::string, int> config)
//{
//	m_remainingSteps = config["Max_Steps"];
//	m_robotRep = robot;
//}

Direction RobotAlgorithm::nextStep(Direction lastMove, bool& finish)
{
	Mode robotMode;
	
	Direction nextStepDirection = Direction::STAY;
	// for testing purposes!
	bool leftSideWall = m_wallSensor->isWall(Direction::LEFT);
	bool rightSideWall = m_wallSensor->isWall(Direction::RIGHT);
	bool downSideWall = m_wallSensor->isWall(Direction::DOWN);
	bool upSideWall = m_wallSensor->isWall(Direction::UP);
	bool isDirty = m_dirtSensor->isDirty();
	int stepsLeft = m_batterySensor->stepsLeft();

	//TODO: next step & Algo! will be implemented next week... 
	updateCurrentLocation(lastMove); // actual location info.
	updateSurroundingMapping(); //no energy required! //based on current location //request 4 direction isWall + isClean on current location
	robotMode = calculateMode(); // BACK if battery level is critical, clean if still have dirt on current location, go to next location based on ALGO in use.
	nextStepDirection = calcNextStep(robotMode);// calc where to go based on mode, Clean ==> STAY, GO - next to clean, BACK - next to Return

//	cout << "ALGO: nextStep: Next proposed step is - " << DirectionToStr.at(nextStepDirection) << endl;
	return nextStepDirection;
}

const string& RobotAlgorithm::getName() const
{
	return m_algoName;
}


const string& RobotAlgorithm::getDescription() const
{
	return m_algoDescription;
}


const uint32_t RobotAlgorithm::getRemainingSteps()
{
	return m_remainingSteps;
}


void RobotAlgorithm::decrementRemainingStep()
{
	m_remainingSteps--;
}

uint32_t RobotAlgorithm::calculateOptimalStepsToCharge()
{
	return 0;
}


uint32_t RobotAlgorithm::calculateChargeRateAndStore()
{
	return 0;
}

// decide whether we on GO, RETURN or CHARGE mode
Mode RobotAlgorithm::calculateMode()
{
	return Mode::DOCK;
}

void  RobotAlgorithm::updateMapScan(Direction dir)
{
	
}

void  RobotAlgorithm::updateSurroundingMapping()
{

}

void  RobotAlgorithm::updateCurrentLocation(Direction dir)
{

}

Direction RobotAlgorithm::calcNextStep(Mode robotMode)
{
	return Direction::STAY;
}