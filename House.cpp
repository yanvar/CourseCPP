#include <iostream>
#include "House.h"
#include <iostream>
#include <fstream>
#include <string>
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

		cout << m_maxStep << " " << m_cols << " " << m_rows << " " << endl;
		
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
			{
				m_origMapping.push_back('W');
			}
		}

		getline(myfile, line); //Skip first line
		int row = 1;
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
		for (int i = 0; i < m_rows; i++) {
			m_origMapping[(m_cols *i)] = 'W';
			m_origMapping[(m_cols * i) + (m_cols-1)] = 'W';
		}
		for (int i = 0; i < m_cols; i++) {
			m_origMapping[((m_rows-1)*(m_cols))+i]='W';
		}
        myfile.close();
    }

	m_currentMapping = m_origMapping;
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
}


int House::GetVectorLocation(int r, int c) const
{
	return ((r * c) + c);
}

char House::GetCurrentState() const {
	return m_currentMapping[GetVectorLocation(m_robotLocation.m_currnetRow, m_robotLocation.m_currnetCol)];
}

bool House::isClean() const
{
	char c = GetCurrentState();
	return (c == '0' || c == ' ' || c == 'D');
}

bool House::isWall(Direction d) const
{
	char c = GetCurrentState();
	return (c == 'W' || c == 'w');
}
bool House::isDirty() const
{
	char c = GetCurrentState();
	return (c > '0' || c <= '9');
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

