#pragma once
#include <iostream>
#include <vector>
#include <map> 

#include "Common.h"
#include "House.h"
#include "Algo.h"
#include "Battery.h"

class Simulation
{
public:
	Simulation();
	int algoGrade;

	bool isWall(Direction d) const;
	bool isDirty() const;
	int stepsLeft() const;

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