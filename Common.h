#pragma once

enum class Direction {
	LEFT, UP, RIGHT, DOWN, STAY
};

// robot may be either in cleaning mode or Return to Base or Charging on Docking station
enum class Mode {
	GO, RETURN, DOCK // DOCK may be included in GO
};


class WallSensorInterface {
	bool isWall(Direction d) const 
	{
		return true;
	}
};

class DirtSensorInterface {
	bool isDirty() const 
	{
		return true;
	}
};

class BatterySensorInterface {
	int stepsLeft() const
	{
		return 0;
	}
};


// TODOs:

/*
//Shulamit/Kosta:

1.toString(Direction to string in Algo.cpp) // needed for printouts, minor


//Michal/Yaniv:
1. int getMaxSteps();   //is missing MAJOR!
2. Direction getLastStep(recommendedDirection);  // to update robot location and house status + return actual step!!!
3. bool isOnDockingLocation();    // returns true if robot is on docking (0,0), or false otherwise

*/