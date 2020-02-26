#pragma once
#include <iostream>
#include <vector>
#include <map> 

#include "..\Common\Common.h"
#include "House.h"
#include "..\RobotAlgorithm.h"
#include "Battery.h"
#include "RobotRepImpl.h"

namespace simulation
{
	class Simulation
	{
	public:
		Simulation(float batteryFullCapacityInSteps, uint32_t batteryConsumptionRate, float m_batteryRechargeRate);
		//int m_algoGrade; // TBD vector vectr TODO

		void addHouse(const char* housePath);
		void addAlgo(RobotAlgorithm* algo);
		uint32_t runSim();

		void printResults();
		void writeResultsToFile();


		typedef struct m_singleSimGrade {
			float cleanGrade = 100;
			int remainingSteps = 0;
		} M_SINGLE_SIM_GRADE;


		float calcSingleSimGrade(bool finish, uint32_t simStepsCntr, House houseIter, Battery& battery, M_SINGLE_SIM_GRADE& m_singleSimGrade);
		void updateResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade);
		float calcAgregatedAlgoGrade(vector<M_SINGLE_SIM_GRADE>& m_algoHouseSimGradee);


		float m_batteryFullCapacityInSteps;
		uint32_t m_batteryConsumptionRate;
		float m_batteryRechargeRate;

	private:

		int updateBatteryChargeLevel(BatteryInterface* battery, common::Direction recommendedDir, bool isOnDocking);

		vector<House> m_allHouses;
		vector<RobotAlgorithm* > m_allAlgos;

		vector<float> m_algosAgregatedGradeList;
		vector<M_SINGLE_SIM_GRADE> m_algoHouseSimGrade;
		float m_totalAlgoGrade = 0;
		float m_singleSimGrade = 0;



	};
}