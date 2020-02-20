#pragma once
#include "Common.h"
#include "HouseInterface.h"
#include <vector>
#include <iostream>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class RobotLocation {
public:
	int m_currnetRow = 0;
	int m_currnetCol = 0;
	void setLocation(int r, int c)
	{
		m_currnetRow = r;
		m_currnetCol = c;
	}

	//RobotLocation getLocation()
};

class House : public HouseInterface
{
public:
	House(const char* path);
	bool isClean() const;
	bool isWall(Direction d) const;
	bool isDirty() const;
	void moveRobot(Direction d);
	void printRoom() const;
	char& operator()(int row, int col);
	double getCleanPercentage() const;
	int getMaxSteps() const;
	Direction getLastStep(Direction d) const;
	bool isOnDockingLocation() const;

private:
	std::vector<char> m_origMapping;
	std::vector<char> m_currentMapping;
	int m_rows, m_cols,m_maxStep;
	RobotLocation m_robotLocation;
	int m_origAccumulatedDirt = 0;

	int getVectorLocation(int r, int c) const;
	char getCurrentState() const;
	void markFirstRawAsWall();
	void markLastRawAsWall();
	void markFirstAndLastColAsWall();
	void fillHouseContent( ifstream& myfile);
	int getRoomAccumulatedDirt() const;
	
};


