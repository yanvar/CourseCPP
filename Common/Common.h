#pragma once
#include <iostream>
#include <string>
#include <map>

namespace common
{
	enum class Direction {
		LEFT, UP, RIGHT, DOWN, STAY
	};

	enum Neighbours_INDEX {
		LEFT, UP, RIGHT, DOWN, NEIGHBOURS_TOTAL
	};

	static std::map<Direction, const char*> DirectionToStr = {
		{Direction::LEFT,  "Left"},
		{Direction::UP,    "Up"},
		{Direction::RIGHT, "Right"},
		{common::Direction::DOWN,  "Down"},
		{common::Direction::STAY,  "Stay"}
	};

	// robot may be either in cleaning mode or Return to Base or Charging on Docking station
	enum class Mode {
		GO, RETURN, DOCK // DOCK may be included in GO
	};


}