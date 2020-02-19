#pragma once

#include <map> 

#define D_BATTERY_MAX_CHARGE      (100) //TBD

class Battery() {
public:
	Battery(int chargeLevelInSteps) :

	// battery measured in "steps" units
	void setBatteryLevelInSteps(int stepsToSet);
	int getBatteryLevelInSteps();
	bool isBatteryEmpty();
	int consumeBatterySingleStep();
	int chargeBatterySingleStep();


private:
	int m_batteryLevelInSteps;

	

	//battery is measured in "steps" units
	int m_batteryFullCapacity;
	int m_batteryConsumptionRate;
	float m_batteryRechargeRate;


}