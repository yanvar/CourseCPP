#include "Simulation.h"

using namespace std;

Simulation::Simulation(float batteryFullCapacityInSteps, uint32_t batteryConsumptionRate, float batteryRechargeRate) :
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

int Simulation::updateBatteryChargeLevel(BatteryInterface* battery,  Direction recommendedDir, bool isOnDocking)
{
	if (isOnDocking && (recommendedDir == Direction::STAY))
		battery->chargeBatteryDuringSingleStep();
	else
		battery->decrementBatterySingleStep();
	
	return battery->stepsLeft();
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
			// steps allocated for house cleanup
			int houseRemainingStepsCntr = houseIter.getMaxSteps();

			// create empty house configuration
			map<string, int> houseConfig;
			// add pair to the map
			houseConfig.insert(std::pair<string, int>("Max_Steps", houseRemainingStepsCntr));

	        // create new battery
			Battery battery(m_batteryFullCapacityInSteps, m_batteryConsumptionRate, m_batteryRechargeRate);
			
			// create RobotREP object and pass it to Algo::init
			RobotRep robotRep = RobotRep(&houseIter, &battery);

			algoIter.init(robotRep, houseConfig);
			
			//// asume battery created with at lease 1 step energy - no checks
			//recommendedDirection = algoIter.nextStep(lastMove, finish);
			//lastMove = houseIter.updateLastStep(recommendedDirection);
			//updateBatteryChargeLevel(&battery, recommendedDirection, houseIter.isOnDockingLocation());

			while (!finish && houseRemainingStepsCntr)
			{
				if ((battery.isBatteryEmpty()) && (!houseIter.isOnDockingLocation()))
					break;
				recommendedDirection = algoIter.nextStep(lastMove, finish);
				lastMove = houseIter.updateLastStep(recommendedDirection);
				updateBatteryChargeLevel(&battery, recommendedDirection, houseIter.isOnDockingLocation());
				houseRemainingStepsCntr--; 
			}

			M_SINGLE_SIM_GRADE singleSimGrade;
			float cleanPercentage;
			cleanPercentage = calcSingleSimGrade(finish, houseRemainingStepsCntr, houseIter, battery, singleSimGrade);
			updateResultsVector(singleSimGrade);
			cout << "Result: Algo - " << " , Hosue - " << endl;
			cout <<"          Clean% = " << singleSimGrade.cleanGrade << "RemainingSteps = " << singleSimGrade.remainingSteps << endl;
		}
		//based on cleanPercentage only
		//calcAgregatedAlgoGrade(Simulation::m_algoHouseSimGrade);
		//updateSingleAgregatedAlgoGrade(singleSimGrade);
	}

	//TODO decideBestAlgo();
	//print ALL !!!

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
		if (finish)
		m_singleSimGrade.remainingSteps = simStepsCntr;
	}

	return m_singleSimGrade.cleanGrade;
}

void Simulation::updateResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{
	m_algoHouseSimGrade.push_back(m_singleSimGrade);
}


void Simulation::printResults()
{
	// loop over ALL houses
	for (auto houseIter : m_allHouses)
	{
		std::cout << "************" << std::endl;
		houseIter.printHouse();
		std::cout << "************" << std::endl;;
	}
}

void Simulation::writeResultsToFile()
{
	ofstream myfile;
	myfile.open("Result.txt");

	// loop over ALL houses
	for (auto houseIter : m_allHouses)
	{
		myfile << "************" << std::endl;
		houseIter.printHouse(myfile);
		myfile << "************" << std::endl;
	}
	myfile.close();
}

//float Simulation::calcAgregatedAlgoGrade(vector<M_SINGLE_SIM_GRADE>& m_algoHouseSimGradee);
//{
//	float sum = 0.0;
//
//	for (auto resultsIter : m_algoHouseSimGradee)
//		sum += resultsIter.cleanGrade;
//
//	return sum / m_algoHouseSimGradee.size();
//}

/*TODO
float Simulation::calcSingleSimGrade(bool finish, int simStepsCntr, House houseIter, Battery&, M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}

void Simulation::updateSimResultsVector(M_SINGLE_SIM_GRADE& m_singleSimGrade)
{

}
*/


