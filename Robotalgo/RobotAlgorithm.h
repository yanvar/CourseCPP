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

		common::State updateState();

		uint32_t m_DiatanceToDockingFromCurLocation = 0;

		//TBD
		uint32_t calculateOptimalStepsToCharge();
		uint32_t calculateChargeRateAndStore();
		// decide whether we on GO, RETURN or CHARGE state
		
		//bool m_finishFlag = false;

	protected: //definitely MUST

		const simulation::WallSensor* m_wallSensor = nullptr;
		const simulation::DirtSensor* m_dirtSensor = nullptr;
		const simulation::BatterySensor* m_batterySensor = nullptr;

		std::string m_algoName;
		std::string m_algoDescription;
		
		bool m_finishFlag = false;
		bool m_houseIsClean = false;
		common::State m_robotState = common::State::CLEAN_MOVE; //reconsider init val.

		uint32_t m_remainingSteps = 0;
		bool m_isCurrentLocationDirty = false;

		// optimization: bool m_wallsOutlineComplete = false;
		float m_calculatedBatteryChargeRate = 1;
		int m_distanceToClosestNotCleanSquare = 1;
		//uint32_t m_DiatanceToDockingFromCurLocation = 0;  // add setter/getter;

		int m_shortestPathToD = 0;
		int m_spareSteps = D_SPARE_BATTERY_STEPS_ON_RETURN;

		

		//CellInfo* getCellInfoByLocation(std::pair<int, int> location, common::Direction d);
		uint32_t getMinimumDistanceToDfromAllNeighbours();
		uint32_t getCellDistanceToDByLocation(std::pair<int, int> location);
		uint32_t setStepsToDockOnMap(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCell);

		//CellInfo* addCellToMap(std::pair<int, int> location, common::Direction neighbourDirection);
		uint32_t distanceToDockingFromLocation(std::pair<int, int> cellCoordinates);
		CellInfo* addNeighbourToMap(std::pair<int, int> neighbourCoordinates, common::Direction NeighborLocationSide, uint32_t stepsToDfromCurrentLocation);
		CellInfo* findCell(std::pair<int, int> neighbourCoordinates);
		void updateDistanceForSingleDirection(std::pair<int, int> neighbourCoordinates, uint32_t stepsToDfromCell);
		void updateStepsToDock(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCell);
		bool isCellExistsOnMap(std::pair<int, int> coordinates);

		
		void updateMapScan(common::Direction dir);
		void updateCurrentLocation(common::Direction lastMove);
		void updateMapping();
		//TODO - replace by michal: void updatePathToDocking(common::Direction d);
		
		
	

		// dynamic map is required!! to mark Undescovered, clean and dirt levels - on discovered map
		//TBD

		// map that holds -  battery level : steps added after 1 charging time;
		std::map<uint32_t, uint32_t> m_calculatedBatteryChargingRate;

		const uint32_t getRemainingSteps();
		void decrementRemainingStep();
		//bool addNewCell();
		bool isCellExist();


		/////////////////////////////////////////////////////////////////////////
		//MAP PART - TODO: should be separated to stand alone object + .h + .cpp files 
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

		typedef std::pair<std::pair<int, int>, CellInfo*> MapCellType;
		std::unordered_map<std::pair<int, int>, CellInfo*, hash_pair> m_mapCells;
		std::pair<int, int> m_robotCurLocation = make_pair(0, 0);
		std::pair<int, int> m_robotClosestNotCleanedSquare = make_pair(0, 0);
		//std::pair<int, int> m_locationToMoveCoordinates = make_pair(0, 0);
		//vector<Direction> m_locationToMoveDirectionsVector = {};

		void updateCurrentLocationInfo(bool isDirty);
		bool addNewCell(std::pair<int, int> cellCoordinates, uint32_t stepsToDfromCurrentLocation, bool isCellWall);
	};
}