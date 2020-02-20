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
	Simulation(uint32_t batteryFullCapacityInSteps, uint32_t batteryConsumptionRate, float m_batteryRechargeRate);
	//int m_algoGrade; // TBD vector vectr TODO

	void addHouse(const char* housePath);
	void addAlgo(Algo algo);
	uint32_t runSim();

	uint32_t printResults();
	uint32_t writeResultsToFile();


	typedef struct m_singleSimGrade {
		float cleanGrade = 100;
		int remainingSteps = 0;
	} M_SINGLE_SIM_GRADE;


	float calcSingleSimGrade(bool finish, uint32_t simStepsCntr, House houseIter, Battery& battery, M_SINGLE_SIM_GRADE& m_singleSimGrade);
	void updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade);


	uint32_t m_batteryFullCapacityInSteps;
	uint32_t m_batteryConsumptionRate;
	float m_batteryRechargeRate;

private:

	vector<House> m_allHouses;
	vector<Algo> m_allAlgos;



	vector<float> m_algosAgregatedGradeList;
	vector<M_SINGLE_SIM_GRADE> m_algoHouseSimGrade;
	float m_totalAlgoGrade = 0;
	float m_singleSimGrade = 0;

	

};