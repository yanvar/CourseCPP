#pragma once
#include <iostream>

#define D_BATTERY_MAX_CHARGE       (100) //TBD - max is needed to prevent overcharge!
#define D_BATTERY_CONSUMPTION_RATE (1)
#define D_BATTERY_ZERO_ENERGY      (0)

class Battery
{
public:
	Battery(int initChargeLevelInSteps);

	// battery measured in "steps" units
	int setBatteryLevelInSteps(int stepsToSet);
	int getBatteryLevelInSteps();
	bool isBatteryEmpty();
	int decrementBatterySingleStep();
	int chargeBatteryDringSingleStep(); // only full steps are count (int)


private:
	// all poewr measurements are normalized to single step unit
	int batteryMaxCapacityInSteps;
	int m_initBatteryLevelInSteps;  // asume it is the MAX power capacity allowed
	int m_currentBatteryLevelInSteps;

	int m_batteryConsumptionRate;
	float m_batteryRechargeRate;
};