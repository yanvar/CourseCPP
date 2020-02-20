#pragma once
#include "BatteryInterface.h"

#include <iostream>

#define D_BATTERY_MAX_CHARGE       (100) //TBD - max is needed to prevent overcharge!
#define D_BATTERY_CONSUMPTION_RATE (1)
#define D_BATTERY_RECHARGE_RATE    (2.5)
#define D_BATTERY_ZERO_ENERGY      (0)

class Battery : public BatteryInterface
{
public:
	Battery(int initChargeLevelInSteps, unsigned int batteryConsumptionRate, float batteryRechargeRate);

	// battery measured in "steps" units
	unsigned int setBatteryLevelInSteps(int stepsToSet);
	bool isBatteryEmpty();
	unsigned int decrementBatterySingleStep();
	unsigned int chargeBatteryDuringSingleStep(); // only full steps are count (int)
	int stepsLeft() const;


private:
	// all poewr measurements are normalized to single step unit
	unsigned int m_batteryMaxCapacityInSteps;
	unsigned int m_initBatteryLevelInSteps;  // asume it is the MAX power capacity allowed
	unsigned int m_currentBatteryLevelInSteps;

	unsigned int m_batteryConsumptionRate;
	float m_batteryRechargeRate;
};