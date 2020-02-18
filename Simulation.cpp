#include "Simulation.h"


using namespace std;

Simulation()
{
}

void addHouse(string housePath)
{
	House house(housePath);
	allHouses.push_back(house);
}
void addAlgo(algo)
{
	Algo algo(algoPath);
	allHouses.push_back(algo);
}
int runSim()
{

	for (auto algoIter : m_allAlgos)
	{
		

		for (auto houseIter : m_allHouses)
		{
			map<string, int> houseMap;
			Direction lastMove = STAY;
			Direction recommendedDirection;
			bool finish = false;
			int simStepsCntr = houseIter.getMaxSteps();
			houseMapInRobot.insert(std::pair<string, int>("Max_Steps", simStepsCntr));

			init(RobotRep & robot, houseMapInRobot);
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



