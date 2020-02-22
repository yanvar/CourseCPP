#include <iostream>
#include "House.h"

using namespace std;

int main_TODO() 
{
	std::cout << "Test:" << endl;
	House h("/home/yanivv/Project/repos/CourseCPP/House1.txt");

	h.printRoom();
//	std::cout << "Clean percentege=" << h.getCleanPercentage()<< std::endl;

	
	std::cout << std::endl;
	House h2("/home/yanivv/Project/repos/CourseCPP/House2.txt");
	h2.printRoom();

	return 0;
}