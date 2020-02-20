#include "Algo.h"

using namespace std;

template<class T_RobotRep>
Algo<T_RobotRep>::Algo()
{
	std::cout << "ALGO: Constructor: Base class object - Algo was created!" << std::endl;
}

template<class T_RobotRep>
void Algo<T_RobotRep>::init(T_RobotRep& robot, std::map<std::string, int> config)
{
	m_remainingSteps = config["Max_Steps"];
	m_robotRep = robot;
}

template<class T_RobotRep>
Direction Algo<T_RobotRep>::nextStep(Direction lastMove, bool& finish)
{
	Direction nextStepDirection = Direction::STAY;

	cout << "ALGO: nextStep: Next proposed step is - " << "STAY" << endl; // implement translation from Direction enum to string!!!
	return nextStepDirection;
}

template<class T_RobotRep>
const string& Algo<T_RobotRep>::getName() const
{
	return m_algoName;
}

template<class T_RobotRep>
const string& Algo<T_RobotRep>::getDescription() const
{
	return m_algoDescription;
}

template<class T_RobotRep>
const int Algo<T_RobotRep>::getRemainingSteps()
{
	return m_remainingSteps;
}

template<class T_RobotRep>
void Algo<T_RobotRep>::decrementRemainingStep()
{
	m_remainingSteps--;
}