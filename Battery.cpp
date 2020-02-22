#include "Battery.h"

using namespace std;


Battery::Battery(float initChargeLevelInSteps = D_BATTERY_MAX_CHARGE, uint32_t batteryConsumptionRate = D_BATTERY_CONSUMPTION_RATE, float batteryRechargeRate = D_BATTERY_RECHARGE_RATE):
	m_batteryMaxCapacityInSteps(initChargeLevelInSteps), m_initBatteryLevelInSteps(initChargeLevelInSteps), m_currentBatteryLevelInSteps(initChargeLevelInSteps),
	m_batteryConsumptionRate(batteryConsumptionRate), m_batteryRechargeRate(batteryRechargeRate)
{
	cout << "BATTERY: Was attached!!! CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
}


float Battery::setBatteryLevelInSteps(float batteryLevelToSet)
{
	m_currentBatteryLevelInSteps = batteryLevelToSet;
	cout << "BATTERY: Charge Level was set. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
	return m_currentBatteryLevelInSteps;
}

int Battery::stepsLeft() const
{
	cout << "BATTERY: Charge Level was checked. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
	return (int)m_currentBatteryLevelInSteps;
}
bool Battery::isBatteryEmpty() const
{
	if (m_currentBatteryLevelInSteps == 0)
	{
		cout << "BATTERY: Emptiness was checked. Battery is EMPTY!" << endl;
		return true;
	}

	cout << "BATTERY: Emptiness was checked. Battery is NOT EMPTY!" << endl;
	return false;
}

float Battery::decrementBatterySingleStep()
{
	if (m_currentBatteryLevelInSteps < m_batteryConsumptionRate)
		m_currentBatteryLevelInSteps = D_BATTERY_ZERO_ENERGY; // current energy - energy consumed during single robot step (measured in robot steps)
	else
		m_currentBatteryLevelInSteps -= m_batteryConsumptionRate;

//	cout << "BATTERY: DecrementBatteryStep. Consumed " << m_batteryConsumptionRate << " steps. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
	return m_currentBatteryLevelInSteps;
}

float Battery::chargeBatteryDuringSingleStep()
{
	m_currentBatteryLevelInSteps += m_batteryRechargeRate; // current energy + energy added during single charging step (measured in robot steps)
	if (m_currentBatteryLevelInSteps > m_initBatteryLevelInSteps)
		m_currentBatteryLevelInSteps = m_initBatteryLevelInSteps;

	cout << "BATTERY: ChargeBatteryStep. Charged by " << m_batteryRechargeRate << " steps. CurrentBatteryLevel is - " << m_currentBatteryLevelInSteps << endl;
	return m_currentBatteryLevelInSteps;
}


