#pragma once
#include <iostream>
#include <vector>

#include "Common.h"
#include "House.h"

class Simulation
{
public:
	Simulation(std::string configDirPath, std::string algoPath);
	int algoGrade;

	bool isWall(Direction d) const;
	bool isDirty() const;
	int stepsLeft() const;

	template<typename RobotRep>
	init(RobotRep& robot, std::Map<std::string, int> config);

	Direction nextStep(Direction lastMove, bool& finish);

	const std::string& getName() const;

	const std::string& getDescription() const;

	void addHouse(string house);
	void addAlgo(string algo);
	int runSim();

	int printResults();
	int writeResultsToFile();


private:
	vector<House> m_allHouses;
	vector<Algo> m_allAlgos;

	vector<float> m_algosGradeList;
	float m_totalAlgoGrade = 0;
	float m_singleSimGrade = 0;

};