#pragma once
#include <iostream>
#include <string>
#include <map>

#include "Common.h"
#include "RobotRep.h"


class Algo
{
	
public:
	Algo();

	template<typename T_RobotRep>
	void init(T_RobotRep& robot, std::map<std::string, int> config)
	{
		m_remainingSteps = config["Max_Steps"];

		m_wallSensor = (robot.getWallSensor());
		m_dirtSensor = (robot.getDirtSensor());
		//batterySensor = &(robot.getBatterySensor());
	}

	Direction nextStep(Direction lastMove, bool& finish);
	const std::string& getName() const;
	const std::string& getDescription() const;

	int calculateOptimalStepsToCharge();
	int calculateChargeRateAndStore();
	// decide whether we on GO, RETURN or CHARGE mode
	Mode calculateMode();


	//void updateMapScan(Direction dir);
	//void updateCurrentLocation(Direction dir);


private:

protected:
	std::string m_algoName;
	std::string m_algoDescription;
	struct currentPosition {
		int x = 0;
		int y = 0;
	};

	// dynamic map is required!! to mark Undescovered, clean and dirt levels - on discovered map
	//TBD

	// map that holds -  battery level : steps added after 1 charging time;
	std::map<int, int> m_calculatedBatteryChargingRate;

	const int getRemainingSteps();
	void decrementRemainingStep();

	int m_remainingSteps;

	WallSensor* m_wallSensor = nullptr;
	DirtSensor* m_dirtSensor = nullptr;
	//BatterySensor* m_batterySensor = nullptr;
	
};