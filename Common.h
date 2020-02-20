#pragma once
#include <iostream>
#include <string>
#include <map>

enum class Direction {
	LEFT, UP, RIGHT, DOWN, STAY
};

static std::map<Direction, const char*> DirectionToStr = {
	{Direction::LEFT,  "Left"},
	{Direction::UP,    "Up"},
	{Direction::RIGHT, "Right"},
	{Direction::DOWN,  "Down"},
	{Direction::STAY,  "Stay"}
};

// robot may be either in cleaning mode or Return to Base or Charging on Docking station
enum class Mode {
	GO, RETURN, DOCK // DOCK may be included in GO
};

/*
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
*/
