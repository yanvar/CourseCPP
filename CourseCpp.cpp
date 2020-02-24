// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Simulation.h"
#include "RandomAlgo.h"
#include "SpiralAlgo.h"
#include "EdgeAlgo.h"
#include "House.h"

#define D_BATTERY_FULL_CAPACITY         (150)
#define D_BATTERY_CONSUMPTION_STEP_RATE (1)
#define D_BATTERY_CHARGE_RATE           (2.5)

using namespace std;

int main()
{
    //k string housePath1 = "House1.txt"; // path depends on PC (should be switched to relative path c_str(); to try
    //k string housePath2 = "House2.txt";

    SpiralAlgo algo1; // create new class + init;
    EdgeAlgo algo2;   // create new class + init;

    Simulation sim(D_BATTERY_FULL_CAPACITY, D_BATTERY_CONSUMPTION_STEP_RATE, D_BATTERY_CHARGE_RATE);

    sim.addHouse("House1.txt");
    sim.addHouse("House2.txt");
	//k sim.addHouse(housePath2);

	sim.addAlgo(&algo1);
	sim.addAlgo(&algo2);

	sim.runSim();

    sim.printResults();
    sim.writeResultsToFile();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
