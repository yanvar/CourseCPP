#pragma once

class Algo()
{
	Algo()

public:
	template<typename RobotRep>
	void init(RobotRep & robot, Map<string, int> config);
	Direction nextStep(Direction lastMove, bool& finish);
	const String& getName() const;
	const String& getDescription() const;



private:

protected:
	string m_algoName;
	string m_algoDescription;

	int getRemainingSteps();
	void decrementRemainingStep();

	int m_remainingSteps;
	template<typename RobotRep> m_robotRep;
}

