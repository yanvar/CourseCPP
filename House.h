#pragma once
#include "Common.h"
#include "HouseInterface.h"
#include <vector>
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class RobotLocation {
public:
	RobotLocation(uint32_t r = 0 , uint32_t c = 0)
	{
		m_currnetRow = r;
		m_currnetCol = c;
	}
	uint32_t m_currnetRow = 0;
	uint32_t m_currnetCol = 0;
	void setLocation(uint32_t r, uint32_t c)
	{
		m_currnetRow = r;
		m_currnetCol = c;
	}

	RobotLocation(const RobotLocation& r2) = default;
	bool operator==(const RobotLocation& other) const
	{
		return (m_currnetRow == other.m_currnetRow) && (m_currnetCol == other.m_currnetCol);
	}

};

class House : public HouseInterface
{
public:
	House(const char* path);
	bool isClean() const;
	bool isWall(Direction d) const;
	bool isDirty() const;
	RobotLocation getLocationByDirection(Direction d) const;
	void printHouse(ostream &myfile = std::cout) const;
	char& operator()(int row, int col);
	float getCleanPercentage() const;
	uint32_t getMaxSteps() const;
	Direction updateLastStep(Direction d);
	bool isOnDockingLocation() const;

private:
	std::vector<char> m_origMapping;
	std::vector<char> m_currentMapping;
	uint32_t m_rows, m_cols, m_maxStep;
	RobotLocation m_robotLocation, m_dockingRobotLocation;
	uint32_t m_origAccumulatedDirt = 0;

	uint32_t getVectorLocation(Direction d) const;
	char getCurrentState(Direction d) const;
	void decreaseDirtCurrentLocation();
	void markAllAsWall();
	void markLastRawAsWall();
	void markFirstAndLastColAsWall();
	void fillHouseContent( ifstream& myfile);
	uint32_t getRoomAccumulatedDirt() const;
	Direction moveRobot(Direction d);
};


