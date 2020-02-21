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
	Battery(int initChargeLevelInSteps, uint32_t batteryConsumptionRate, float batteryRechargeRate);

	// battery measured in "steps" units
	uint32_t setBatteryLevelInSteps(int stepsToSet);
	bool isBatteryEmpty();
	uint32_t decrementBatterySingleStep();
	uint32_t chargeBatteryDuringSingleStep(); // only full steps are count (int)
	int stepsLeft() const;


private:
	// all poewr measurements are normalized to single step unit
	uint32_t m_batteryMaxCapacityInSteps;
	uint32_t m_initBatteryLevelInSteps;  // asume it is the MAX power capacity allowed
	uint32_t m_currentBatteryLevelInSteps;

	uint32_t m_batteryConsumptionRate;
	float m_batteryRechargeRate;
};