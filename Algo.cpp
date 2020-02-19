#include "Algo.h"
#include "Common.h"

template<typename RobotRep>
void init(RobotRep& robot, Map<string, int> config)
{
	m_remainingSteps = config["Max_Steps"];
	m_robotRep = robot;
}

Direction nextStep(Direction lastMove, bool& finish)
{
	return STAY;
}

const String& getName() const
{
	return m_algoName;
}

const String& getDescription() const
{
	return m_algoDescription;
}

int getRemainingSteps()
{
	return m_remainingSteps;
}
void decrementRemainingStep()
{
	m_remainingSteps--;
}