// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Simulation.h"


using namespace std;

int main()
{
    string housePath1 = "C:\Users\Yaniv Vardi\source\repos\test\ConsoleApplication1\ConfigHomes\house1.txt";
    string housePath2 = "C:\Users\Yaniv Vardi\source\repos\test\ConsoleApplication1\ConfigHomes\house2.txt";

    string algo1 = // create new class;
    string algo2 = // create new class;



    Simulation sim();

    Simulation::addHouse(housePath1);
    Simulation::addHouse(housePath2);
    Simulation::addAlgo(algoPath1);
    Simulation::addAlgo(algoPath2);

    Simulation::runSim();

    Simulation::printResults();
    Simulation::writeResultsToFile();
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
