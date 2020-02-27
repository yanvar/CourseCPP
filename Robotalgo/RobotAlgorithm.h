#pragma once
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

#include "CellInfo.h"
#include "..\Common\Common.h"
#include "..\Simulation\RobotRepImpl.h"

#define D_DOCKING_LOCATION                make_pair(0,0)
#define D_SPARE_BATTERY_STEPS_ON_RETURN   (0)

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
		virtual const std::string& getName() const= 0;
		virtual const std::string& getDescription() const = 0;


		//TBD
		uint32_t calculateOptimalStepsToCharge();
		uint32_t calculateChargeRateAndStore();
		// decide whether we on GO, RETURN or CHARGE state
		common::State calculateState();
		bool m_finishFlag = false;

	protected: //definitely MUST
		std::string m_algoName;
		std::string m_algoDescription;
		//bool m_finishFlag = false;
		bool m_houseIsClean = false;
		common::State m_robotState = common::State::CLEAN_MOVE; //reconsider init val.

		uint32_t m_remainingSteps = 0;
		bool m_isCurrentLocationDirty = false;

		// optimization: bool m_wallsOutlineComplete = false;
		float m_calculatedBatteryChargeRate = 1;
		int m_distanceToClosestNotCleanSquare = 1;

		int m_shortestPathToD = 0;
		int m_spareSteps = D_SPARE_BATTERY_STEPS_ON_RETURN;

		// A hash function used to hash a pair of any kind 
		struct hash_pair {
			template <class T1, class T2>
			size_t operator()(const pair<T1, T2>& p) const
			{
				auto hash1 = hash<T1>{}(p.first);
				auto hash2 = hash<T2>{}(p.second);
				return hash1 ^ hash2;
			}
		};

		std::unordered_map<std::pair<int, int>, CellInfo*, hash_pair> m_mapCells;
		std::pair<int, int> m_robotCurLocation = make_pair(0, 0);
		std::pair<int, int> m_robotClosestNotCleanedSquare = make_pair(0, 0);
		//std::pair<int, int> m_locationToMoveCoordinates = make_pair(0, 0);
		//vector<Direction> m_locationToMoveDirectionsVector = {};

		

		const simulation::WallSensor* m_wallSensor = nullptr;
		const simulation::DirtSensor* m_dirtSensor = nullptr;
		const simulation::BatterySensor* m_batterySensor = nullptr;


		/////////////////////////////////////////////////////////////////////////

		
		void updateMapScan(common::Direction dir);
		void updateCurrentLocation(common::Direction lastMove);
		void updateMapping();
		
		
	

		// dynamic map is required!! to mark Undescovered, clean and dirt levels - on discovered map
		//TBD

		// map that holds -  battery level : steps added after 1 charging time;
		std::map<uint32_t, uint32_t> m_calculatedBatteryChargingRate;

		const uint32_t getRemainingSteps();
		void decrementRemainingStep();
		bool addNewCell();
		bool isCellExist();


		
	};
}