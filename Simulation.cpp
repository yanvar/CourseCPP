#include "Simulation.h"


using namespace std;

Simulation()
{
}

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

			//TODO: create RobotREP object and pass it to init
			

			init(RobotRep & robot, houseConfig);
			Battery battery(int chargedCapacity);

			recommendedDirection = robot.nextStep(lastMove, finish);
			while (!finish && simStepsCntr)
			{
				lastMove = houseIter.getLastStep(recommendedDirection);
				recommendedDirection = robot.nextStep(lastMove, finish);

				simStepsCntr--;
			}

			calcSingleSimGrade(finish, simStepsCntr, houseIter);
		}
}

int printResults();
int writeResultsToFile();



