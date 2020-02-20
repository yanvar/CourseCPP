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


	typedef struct m_singleSimGrade {
		float cleanGrade = 100;
		int remainingSteps = 0;
	} M_SINGLE_SIM_GRADE;


	float calcSingleSimGrade(bool finish, int simStepsCntr, House houseIter, Battery& battery, M_SINGLE_SIM_GRADE& m_singleSimGrade);
	void updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade);


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