#pragma once
#include <iostream>
#include <string>
#include <map>

#include "..\Common\Common.h"
#include "..\Simulation\RobotRepImpl.h"

namespace robotalgo
{

	class RobotAlgorithm
	{

	public:
		RobotAlgorithm();

		template<typename RobotRep>
		void init(RobotRep& robot, std::map<std::string, int> config)
		{
			m_remainingSteps = config["Max_Steps"];

			m_wallSensor = &(robot.getWallSensor());
			m_dirtSensor = &(robot.getDirtSensor());
			m_batterySensor = &(robot.getBatterySensor());
		}

		virtual common::Direction nextStep(common::Direction lastMove, bool& finish) = 0;
		const std::string& getName() const;
		const std::string& getDescription() const;

		uint32_t calculateOptimalStepsToCharge();
		uint32_t calculateChargeRateAndStore();
		// decide whether we on GO, RETURN or CHARGE mode
		common::Mode calculateMode();


		void updateMapScan(common::Direction dir);
		void updateCurrentLocation(common::Direction dir);
		void updateSurroundingMapping();
		common::Direction calcNextStep(common::Mode robotMode);


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

		const simulation::WallSensor* m_wallSensor = nullptr;
		const simulation::DirtSensor* m_dirtSensor = nullptr;
		const simulation::BatterySensor* m_batterySensor = nullptr;

	};
}