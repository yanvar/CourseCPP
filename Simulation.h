#pragma once
#include <iostream>
#include <vector>
#include <map> 

#include "Common.h"
#include "House.h"
#include "Algo.h"
#include "Battery.h"
#include "RobotRep.h"

class Simulation
{
public:
	Simulation(int batteryFullCapacityInSteps, int batteryConsumptionRate, float m_batteryRechargeRate);
	int algoGrade; // TBD vector vectr

	void addHouse(const char* housePath);
	void addAlgo(Algo algo);
	int runSim();

	int printResults();
	int writeResultsToFile();

	void calcSingleSimGrade(finish, simStepsCntr, houseIter, Battery&, M_SINGLE_SIM_GRADE & m_singleSimGrade);
	void updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade);
	void updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade);

	typedef struct m_singleSimGrade {
		float cleanGrade = 100;
		int remainingSteps = 0;
	} M_SINGLE_SIM_GRADE;

	int m_batteryFullCapacityInSteps;
	int m_batteryConsumptionRate;
	float m_batteryRechargeRate;

private:

	vector<House> m_allHouses;
	vector<Algo> m_allAlgos;



	vector<float> m_algosAgregatedGradeList;
	vector<M_SINGLE_SIM_GRADE> m_algoHouseSimGrade;
	float m_totalAlgoGrade = 0;
	float m_singleSimGrade = 0;

	

};