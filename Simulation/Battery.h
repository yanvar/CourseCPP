#pragma once
#include "BatteryInterface.h"

#include <iostream>

#define D_BATTERY_MAX_CHARGE       (100) //TBD - max is needed to prevent overcharge!
#define D_BATTERY_CONSUMPTION_RATE (1)
#define D_BATTERY_RECHARGE_RATE    (2.5)
#define D_BATTERY_ZERO_ENERGY      (0)

namespace simulation
{

	class Battery : public BatteryInterface
	{
	public:
		Battery(float initChargeLevelInSteps, uint32_t batteryConsumptionRate, float batteryRechargeRate);

		// battery measured in "steps" units
		float setBatteryLevelInSteps(float stepsToSet);
		bool isBatteryEmpty() const;
		float decrementBatterySingleStep();
		float chargeBatteryDuringSingleStep(); // only full steps are count (int)
		int stepsLeft() const;

	private:
		// all poewr measurements are normalized to single step unit
		float m_batteryMaxCapacityInSteps;
		float m_initBatteryLevelInSteps;  // asume it is the MAX power capacity allowed
		float m_currentBatteryLevelInSteps;

		uint32_t m_batteryConsumptionRate;
		float m_batteryRechargeRate;
	};
}