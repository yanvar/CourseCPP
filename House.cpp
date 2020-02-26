#include <iostream>
#include "House.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Common\Common.h"

using namespace std;
using namespace common;

House::House(const char* path)
{
    string line;
    ifstream myfile(path);
    if (myfile.is_open())
    {
		std::getline(myfile, line);//desc
		std::getline(myfile, line);//max_step
		m_maxStep = stoi(line);
		std::getline(myfile, line, ',');
		m_rows = stoi(line);
		std::getline(myfile, line);
		m_cols= stoi(line);
		markAllAsWall();
		getline(myfile, line); //Skip first line
		fillHouseContent(myfile);
		markLastRawAsWall();
		markFirstAndLastColAsWall();
        myfile.close();
    }
	else
	{
		cout << "Failed to open file " << path << ", existing" << endl;
		exit(0);
	}
	
	m_currentMapping = m_origMapping;
	m_origAccumulatedDirt = getRoomAccumulatedDirt();

	cout << "House /""" << path << "/"" was created!" << endl;
}

uint32_t House::getRoomAccumulatedDirt() const
{
	int accumulatedDirt = 0;
	for(auto c : m_currentMapping)
	{
		if (c > '0' && c <= '9')
		{
			accumulatedDirt += (c - '0');
		}
	}
	return accumulatedDirt;
}  

uint32_t House::getMaxSteps() const
{
	return m_maxStep;
}

Direction House::updateLastStep(Direction recommendedDirection)
{
	//TODO: check if recommendedDirection!=STAY && !onDocking && ...
	decreaseDirtCurrentLocation();
	if (recommendedDirection == Direction::STAY)
		return Direction::STAY;
	return moveRobot(recommendedDirection);
}
 bool House::isOnDockingLocation() const
{
	return (m_dockingRobotLocation == m_robotLocation); 
}

void House::fillHouseContent(ifstream& myfile)
{
	uint32_t row = 1;
	string line;
	while (getline(myfile, line))
	{
		if (row == m_rows)
			break;
		uint32_t col = 0;
		for (auto c : line) {
			if (col == m_cols)
				break;
			m_origMapping[((size_t)row*m_cols) + col] = (c);
			if (c == 'D')
			{
				m_robotLocation.setLocation(row, col);
				m_dockingRobotLocation = m_robotLocation;
			}
			col++;
		}
		row++;
	}
}

void House::markAllAsWall()
{
	for (uint32_t i = 0; i < m_rows; i++)
	{
		for (uint32_t j = 0; j < m_cols; j++)
		{
			m_origMapping.push_back('W');
		}
	}	
}

void House::markLastRawAsWall()
{
	for (uint32_t i = 0; i < m_cols; i++)
	{
		m_origMapping[(((size_t)m_rows-1)*(m_cols))+i]='W';
	}
}

void House::markFirstAndLastColAsWall()
{
	for (uint32_t i = 0; i < m_rows; i++) 
	{
		m_origMapping[((size_t)m_cols *i)] = 'W';
		m_origMapping[((size_t)m_cols * i) + (m_cols-1)] = 'W';
	}
	
}

void House::printHouse(ostream &resultfile) const
{
	std::string output;
	for (uint32_t i = 0; i < m_rows; i++)
	{
		for (uint32_t j = 0; j < m_cols; j++)
		{
			output += (m_currentMapping[((size_t)m_cols * i) + j]);
		}
		output += '\n';
	}
	output += ("Robot location: " + std::to_string(m_robotLocation.m_currnetRow) +
				' ' + std::to_string(m_robotLocation.m_currnetCol) + '\n');
	output += ("Room dirt level = " + std::to_string(m_origAccumulatedDirt) + '\n');
	
	resultfile << output;
}

RobotLocation House::getLocationByDirection(Direction d) const {
	if (d == Direction::LEFT)
	{
		return RobotLocation(m_robotLocation.m_currnetRow, m_robotLocation.m_currnetCol - 1);
	}
	if (d == Direction::UP)
	{
		return RobotLocation(m_robotLocation.m_currnetRow + 1, m_robotLocation.m_currnetCol);
	}
	if (d == Direction::RIGHT)
	{
		return RobotLocation(m_robotLocation.m_currnetRow, m_robotLocation.m_currnetCol + 1);
	}
	if (d == Direction::DOWN)
	{
		return RobotLocation(m_robotLocation.m_currnetRow - 1, m_robotLocation.m_currnetCol);
	}

	//STAY
	return RobotLocation(m_robotLocation.m_currnetRow, m_robotLocation.m_currnetCol);
}

uint32_t House::getVectorLocation(Direction d = Direction::STAY) const
{
	RobotLocation tmpLocation = getLocationByDirection(d);
	return ((tmpLocation.m_currnetRow * m_cols) + tmpLocation.m_currnetCol);
}

char& House::operator()(int row, int col)
{
	return m_currentMapping[((size_t)row*m_cols)+col];
}

char House::getCurrentState(Direction d = Direction::STAY) const {
	return m_currentMapping[getVectorLocation(d)];
}

void House::decreaseDirtCurrentLocation() {
	if (isDirty())
	{
		m_currentMapping[getVectorLocation()] -= 1;
	}
}

bool House::isClean() const
{
	char c = getCurrentState();
	return (c == '0' || c == ' ' || c == 'D');
}

bool House::isWall(Direction d) const
{
	char c = getCurrentState(d);
	return (c == 'W' || c == 'w');
}

bool House::isDirty() const
{
	char c = getCurrentState();
	return (c > '0' && c <= '9');
}


Direction House::moveRobot(Direction d)
{
	int index = getVectorLocation(d);
	if (m_currentMapping[index] == 'W')
		return Direction::STAY;

	m_robotLocation = getLocationByDirection(d);
	return d;
}


float House::getCleanPercentage() const
{
	float dirtPercent = (float)getRoomAccumulatedDirt() / m_origAccumulatedDirt;
	return (1-dirtPercent)*100;
}
