#include "Simulation.h"

using namespace std;

Simulation::Simulation(uint32_t batteryFullCapacityInSteps, uint32_t batteryConsumptionRate, float batteryRechargeRate) :
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

uint32_t Simulation::runSim()
{
	// loop over ALL algos
	for (auto algoIter : m_allAlgos)
	{
		// loop over ALL houses
		for(auto houseIter: m_allHouses)
		{
			Direction lastMove = Direction::STAY;
			Direction recommendedDirection;
			
		//	auto houseIter = &m_allHouses[i];
			bool finish = false;
			int houseRemainingStepsCntr = houseIter.getMaxSteps();

			// create empty house configuration
			map<string, int> houseConfig;
			// add pair to the map
			houseConfig.insert(std::pair<string, int>("Max_Steps", houseRemainingStepsCntr));

	        // create new battery
			Battery battery(m_batteryFullCapacityInSteps, m_batteryConsumptionRate, m_batteryRechargeRate);
			
			//TODO: create RobotREP object and pass it to init - TOCHECK REF DEFINITION
			RobotRep robotRep = RobotRep(&houseIter, battery);
			//RobotRep robotRep = RobotRep(houseIter);

			algoIter.init(robotRep, houseConfig);
			
			recommendedDirection = algoIter.nextStep(lastMove, finish);
			while (!finish && houseRemainingStepsCntr)
			{
				lastMove = houseIter.updateLastStep(recommendedDirection);
				recommendedDirection = algoIter.nextStep(lastMove, finish);

				houseRemainingStepsCntr--;
				if ((battery.decrementBatterySingleStep() == 0) && (!houseIter.isOnDockingLocation()))
					break;
			}

			M_SINGLE_SIM_GRADE singleSimGrade;

			//todo calcSingleSimGrade(finish, houseRemainingStepsCntr, houseIter, battery, singleSimGrade);
			updateSimResultsVector(singleSimGrade);
		}
		// TODO
		//calcSingleAgregatedAlgoGrade(simStepsCntr, houseIter, finalRobotLocation, battery, singleSimGrade);
		//updateSingleAgregatedAlgoGrade(singleSimGrade);
	}

	//TODO decideBestAlgo();
	//print ALL !!!

	//TODO
	return 0;
}



float Simulation::calcSingleSimGrade(bool finish, uint32_t simStepsCntr, House houseIter, Battery& battery, M_SINGLE_SIM_GRADE& m_singleSimGrade)
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

	return 0; //TODO
}

void Simulation::updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{
	m_algoHouseSimGrade.push_back(m_singleSimGrade);
}


uint32_t Simulation::printResults()
{
	return 0; //TODO
}

uint32_t Simulation::writeResultsToFile()
{
	return 0; //TODO
}

/*TODO
float Simulation::calcSingleSimGrade(bool finish, int simStepsCntr, House houseIter, Battery&, M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}

void Simulation::updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}
*/


