#include "Battery.h"

using namespace std;

//class Battery()
//{
//public:
	Battery::Battery(int initChargeLevelInSteps) : m_initBatteryLevelInSteps(initChargeLevelInSteps), m_currentBatteryLevelInSteps(initChargeLevelInSteps) 
	{
		cout << "BATTERY: Was attached!!! CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
	}

	int Battery::setBatteryLevelInSteps(int batteryLevelToSet)
	{
		m_currentBatteryLevelInSteps = batteryLevelToSet;
		cout << "BATTERY: Charge Level was set. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
		return m_currentBatteryLevelInSteps;
	}

	int Battery::getBatteryLevelInSteps()
	{
		cout << "BATTERY: Charge Level was checked. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
		return m_currentBatteryLevelInSteps;
	}
	bool Battery::isBatteryEmpty()
	{
		if (m_currentBatteryLevelInSteps == 0)
		{
			cout << "BATTERY: Emptiness was checked. Battery is EMPTY!" << endl;
			return true;
		}

		cout << "BATTERY: Emptiness was checked. Battery is NOT EMPTY!" << endl;
		return false;
	}

	int Battery::decrementBatterySingleStep()
	{
		m_currentBatteryLevelInSteps -= m_batteryConsumptionRate; // current energy - energy consumed during single robot step (measured in robot steps)
		if (m_currentBatteryLevelInSteps < D_BATTERY_ZERO_ENERGY)
			m_currentBatteryLevelInSteps = D_BATTERY_ZERO_ENERGY;

		cout << "BATTERY: DecrementBatteryStep. Consumed " << m_batteryConsumptionRate << " steps. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;

		return m_currentBatteryLevelInSteps;
	}

	int Battery::chargeBatteryDringSingleStep()
	{
		m_currentBatteryLevelInSteps += (int)m_batteryRechargeRate; // current energy + energy added during single charging step (measured in robot steps)
		if (m_currentBatteryLevelInSteps > m_initBatteryLevelInSteps)
			m_currentBatteryLevelInSteps = m_initBatteryLevelInSteps;

		cout << "BATTERY: ChargeBatteryStep. Charged by " << m_batteryRechargeRate << " steps. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;

		return m_currentBatteryLevelInSteps;
	}
//}

