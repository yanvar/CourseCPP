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

	}
};

class DirtSensorInterface {
	bool isDirty() const 
	{

	}
};

class BatterySensorInterface {
	int stepsLeft() const
	{

	}
};
