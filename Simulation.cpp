#include "Simulation.h"

using namespace std;

Simulation::Simulation(int batteryFullCapacityInSteps, int batteryConsumptionRate, float batteryRechargeRate) :
	m_batteryFullCapacityInSteps(batteryFullCapacityInSteps), m_batteryConsumptionRate(batteryConsumptionRate), m_batteryRechargeRate(batteryRechargeRate)
{}

void Simulation::addHouse(const char * housePath)
{
	House house(housePath);
	m_allHouses.push_back(house);
}

void Simulation::addAlgo(Algo algo)
{
	//k Algo algo(algo);
	m_allAlgos.push_back(algo);
}

int Simulation::runSim()
{
	// loop over ALL algos
	for (auto algoIter : m_allAlgos)
	{

		// loop over ALL houses
		for (auto houseIter : m_allHouses)
		{
			Direction lastMove = Direction::STAY;
			Direction recommendedDirection;
			bool finish = false;
			int houseRemainingStepsCntr = houseIter.getMaxSteps();

			// create empty house configuration
			map<string, int> houseConfig;
			// add pair to the map
			houseConfig.insert(std::pair<string, int>("Max_Steps", houseRemainingStepsCntr));

	        // create new battery
			Battery battery(m_batteryFullCapacityInSteps, m_batteryConsumptionRate, m_batteryRechargeRate);
			
			//TODO: create RobotREP object and pass it to init - TOCHECK REF DEFINITION
			RobotRep robotRep = RobotRep(houseIter, battery);

			algoIter.init(robotRep, houseConfig);
			
			recommendedDirection = algoIter.nextStep(lastMove, finish);
			while (!finish && houseRemainingStepsCntr)
			{
				lastMove = houseIter.getLastStep(recommendedDirection);
				recommendedDirection = algoIter.nextStep(lastMove, finish);

				houseRemainingStepsCntr--;
				if ((battery.decrementBatterySingleStep() == 0) && (!houseIter.isOnDockingLocation()))
					break;
			}

			M_SINGLE_SIM_GRADE singleSimGrade;

			calcSingleSimGrade(finish, houseRemainingStepsCntr, houseIter, battery, singleSimGrade);
			updateSimResultsVector(singleSimGrade);
		}
		calcSingleAgregatedAlgoGrade(finish, simStepsCntr, houseIter, finalRobotLocation, battery, singleSimGrade);
		updateSingleAgregatedAlgoGrade(singleSimGrade);
	}

	decideBestAlgo();
	//print ALL !!!
}



	void Simulation::calcSingleSimGrade(finish, simStepsCntr, houseIter, finalRobotLocation, battery, m_singleSimGrade)
	{

		if (!houseIter.isOnDockingLocation())
		{
			m_singleSimGrade.cleanGrade = 0;
			m_singleSimGrade.remainingSteps = 0;
		}
		else
		{
			m_singleSimGrade.cleanGrade = houseIter.getCleanPercentage();
			m_singleSimGrade.remainingSteps = simStepsCntr;
		}
	}
	void Simulation::updateSimResultsVectorvoid(M_SINGLE_SIM_GRADE& m_singleSimGrade)
	{
		m_algoHouseSimGrade.push_back(m_singleSimGrade);
	}


int Simulation::printResults()
{

}

int Simulation::writeResultsToFile();
{

}

float Simulation::calcSingleSimGrade(finish, simStepsCntr, houseIter, Battery&, M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}

void Simulation::updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}

void Simulation::updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}



