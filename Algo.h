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

		m_wallSensor = &(robot.getWallSensor());
		m_dirtSensor = &(robot.getDirtSensor());
		//m_batterySensor = (robot.getBatterySensor());
	}

	Direction nextStep(Direction lastMove, bool& finish);
	const std::string& getName() const;
	const std::string& getDescription() const;

	uint32_t calculateOptimalStepsToCharge();
	uint32_t calculateChargeRateAndStore();
	// decide whether we on GO, RETURN or CHARGE mode
	Mode calculateMode();


	void updateMapScan(Direction dir);
	void updateCurrentLocation(Direction dir);
	void updateSurroundingMapping();
	Direction calcNextStep(Mode robotMode);


private:

protected:
	std::string m_algoName;
	std::string m_algoDescription;
	struct currentPosition {
		uint32_t x = 0;
		uint32_t y = 0;
	};

	// dynamic map is required!! to mark Undescovered, clean and dirt levels - on discovered map
	//TBD

	// map that holds -  battery level : steps added after 1 charging time;
	std::map<uint32_t, uint32_t> m_calculatedBatteryChargingRate;

	const uint32_t getRemainingSteps();
	void decrementRemainingStep();

	uint32_t m_remainingSteps = 0;

	const WallSensor *m_wallSensor;
	const DirtSensorInterface* m_dirtSensor;
	//BatterySensorInterface* m_batterySensor = nullptr;
	
};