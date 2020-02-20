#include <iostream>
#include "House.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Common.h"

using namespace std;

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
		markFirstRawAsWall();				
		getline(myfile, line); //Skip first line
		fillHouseContent(myfile);
		markLastRawAsWall();
		markFirstAndLastColAsWall();
        myfile.close();
    }
	m_currentMapping = m_origMapping;
	m_origAccumulatedDirt = getRoomAccumulatedDirt();

	cout << "House /""" << path << "/"" was created!" << endl;
}

int House::getRoomAccumulatedDirt() const
{
	int accumulatedDirt = 0;
	for(auto c : m_currentMapping)
	{

		if (c > '0' && c <= '9')
		{
			accumulatedDirt += c - '0';
		}
	}
	return accumulatedDirt;
}  

int House::getMaxSteps() const
{
	return m_maxStep; //TODO**************
}

Direction House::getLastStep(Direction d) const
{
	return Direction::STAY; //TODO**************
}
 bool House::isOnDockingLocation() const
{
	return true; //TODO**************
}


void House::fillHouseContent(ifstream& myfile)
{
		int row = 1;
		string line;
        while (getline(myfile, line))
        {
			if (row == m_rows)
				break;
			int col = 0;
			for (auto c : line) {
				if (col == m_cols)
					break;
				m_origMapping[row*m_cols + col] = (c);
				if (c == 'D')
					m_robotLocation.setLocation(row, col);
				col++;
			}
			row++;
        }
}

void House::markFirstRawAsWall()
{
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
			{
				m_origMapping.push_back('W');
			}
		}	
}

void House::markLastRawAsWall()
{
	for (int i = 0; i < m_cols; i++)
	{
		m_origMapping[((m_rows-1)*(m_cols))+i]='W';	
	}
}

void House::markFirstAndLastColAsWall()
{
	for (int i = 0; i < m_rows; i++) 
	{
		m_origMapping[(m_cols *i)] = 'W';
		m_origMapping[(m_cols * i) + (m_cols-1)] = 'W';
	}
	
}

void House::printRoom() const
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			cout << m_origMapping[(m_cols * i) + j];
		}
		cout << endl;
	}
	cout << "Robot location: " << m_robotLocation.m_currnetRow << " " << m_robotLocation.m_currnetCol << endl;
	cout << "Room dirt level = " << m_origAccumulatedDirt << endl;
}


int House::getVectorLocation(int r, int c) const
{
	return ((r * m_cols) + c);
}

char& House::operator()(int row, int col)
{
	return m_currentMapping[(row*m_cols)+col];
}

char House::getCurrentState() const {
	return m_currentMapping[getVectorLocation(m_robotLocation.m_currnetRow, m_robotLocation.m_currnetCol)];
}


bool House::isClean() const
{
	char c = getCurrentState();
	return (c == '0' || c == ' ' || c == 'D');
}

bool House::isWall(Direction d) const
{
	char c = getCurrentState();  //TODO !!! should be fixed. location should be updated according to requested direction! E.g. LEFT ==> col+1, UP ==> row -1, etc... (then return compare to W!!
	return (c == 'W' || c == 'w');
}
bool House::isDirty() const
{
	char c = getCurrentState();
	return (c > '0' && c <= '9');
}

void House::moveRobot(Direction d)
{
	if (d == Direction::LEFT)
	{
		m_robotLocation.setLocation(m_rows, m_cols - 1);
	}
	if (d == Direction::UP)
	{
		m_robotLocation.setLocation(m_rows + 1, m_cols);
	}
	if (d == Direction::RIGHT)
	{
		m_robotLocation.setLocation(m_rows, m_cols + 1);
	}
	if (d == Direction::DOWN)
	{
		m_robotLocation.setLocation(m_rows - 1, m_cols);
	}

}


float House::getCleanPercentage() const
{
	float dirtPercent = (float)getRoomAccumulatedDirt() / m_origAccumulatedDirt;
	return (1-dirtPercent)*100;
}
