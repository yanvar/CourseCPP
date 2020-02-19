#include "Simulation.h"


using namespace std;

Simulation(int maxSteps, int batteryFullCapacityInSteps, int batteryConsumptionRate, float batteryRechargeRate) :
	m_maxSteps(maxSteps), m_batteryFullCapacityInSteps(batteryFullCapacityInSteps), m_batteryConsumptionRate(batteryConsumptionRate), m_batteryRechargeRate(batteryRechargeRate))
{}

void addHouse(string housePath)
{
	House house(housePath);
	m_allHouses.push_back(house);
}
void addAlgo(algo)
{
	Algo algo(algoPath);
	m_allAlgos.push_back(algo);
}
int runSim()
{
	// loop over ALL algos
	for (auto algoIter : m_allAlgos)
	{

		// loop over ALL houses
		for (auto houseIter : m_allHouses)
		{
			Direction lastMove = STAY;
			Direction recommendedDirection;
			bool finish = false;
			int simStepsCntr = houseIter.getMaxSteps();

			// create empty house configuration
			map<string, int> houseConfig;
			// add pair to the map
			houseConfig.insert(std::pair<string, int>("Max_Steps", simStepsCntr));
			Battery battery(int m_batteryFullCapacityInSteps);
			
			//TODO: create RobotREP object and pass it to init
			RobotRep& robotRep = RobotRep(houseIter, battery);

			init(robotRep, houseConfig);
			
			
			recommendedDirection = robot.nextStep(lastMove, finish);
			while (!finish && simStepsCntr)
			{
				lastMove = houseIter.getLastStep(recommendedDirection);
				recommendedDirection = robot.nextStep(lastMove, finish);

				simStepsCntr--;
				if (battery.decrementBatterySingleStep() == 0) && (!houseIter.isOnDockingLocation()))
				break;

			}

			M_SINGLE_SIM_GRADE singleSimGrade;

			calcSingleSimGrade(finish, simStepsCntr, houseIter, finalRobotLocation, battery, singleSimGrade);
			updateSimResultsVector(singleSimGrade);
		}
		calcSingleAgregatedAlgoGrade(finish, simStepsCntr, houseIter, finalRobotLocation, battery, singleSimGrade);
		updateSingleAgregatedAlgoGrade(singleSimGrade);
	}

	decideBestAlgo();
	print ALL !!!
}



	void calcSingleSimGrade(finish, simStepsCntr, houseIter, finalRobotLocation, battery, m_singleSimGrade)
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
	void updateSimResultsVectorvoid(M_SINGLE_SIM_GRADE& m_singleSimGrade)
	{
		m_algoHouseSimGrade.push_back(m_singleSimGrade);
	}


int printResults();
int writeResultsToFile();



