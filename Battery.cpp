
class Battery() {
public:
	Battery(int chargeLevelInSteps) : m_batteryLevelInSteps(chargeLevelInSteps) {}

	void setBatteryLevelInSteps(int stepsToSet)
	{
		m_batteryLevelInSteps = stepsToSet;
	}

	int getBatteryLevelInSteps()
	{
		return m_batteryLevelInSteps;
	}
	bool isBatteryEmpty()
	{
		if (m_batteryLevelInSteps == 0)
			return true;
		return false;
	}


	int decrementBatterySingleStep()
	{
		if (m_batteryLevelInSteps == 0)
			return true;
	}

	int chargeBatterySingleStep();
