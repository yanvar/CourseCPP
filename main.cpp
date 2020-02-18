#include <iostream>
#include "House.h"

int main() 
{
	std::cout << "Test";
	House h("C:\/Users\/jonat\/source\/repos\/Project6\/Project6\/House1.txt");
	h.printRoom();
	std::cout << h.isClean() << std::endl;

	std::cout << std::endl;
	House h2("C:\/Users\/jonat\/source\/repos\/Project6\/Project6\/House2.txt");
	h2.printRoom();

	return 0;
}