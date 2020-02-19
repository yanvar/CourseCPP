#pragma once

class Algo()
{
	Algo()

public:
	template<typename RobotRep>
	void init(RobotRep & robot, Map<string, int> config);
	Direction nextStep(Direction lastMove, bool& finish);
	const String& getName() const;
	const String& getDescription() const;

	int calculateOptimalStepsToCharge();
	int calculateChargeRateAndStore();
	// decide whether we on GO, RETURN or CHARGE mode
	Mode calculateMode();


	void updateMapScan(Direction dir);
	void updateCurrentLocation(Direction dir);


private:

protected:
	string m_algoName;
	string m_algoDescription;
	struct currentPosition {
		int x = 0;
		int y = 0;
	};
	
	// dynamic map is required!! to mark Undescovered, clean and dirt levels - on discovered map
	//TBD

	// map that holds -  battery level : steps added after 1 charging time;
	map<int, int> m_calculatedBatteryChargingRate;

	int getRemainingSteps();
	void decrementRemainingStep();

	int m_remainingSteps;
	template<typename RobotRep> m_robotRep;
}

