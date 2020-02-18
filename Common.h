#pragma once



enum class Direction {
	LEFT, UP, RIGHT, DOWN, STAY
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
