#pragma once
#include <iostream>
#include <string>
#include <map>

#define D_MAX_INT_VAL (0xFFFFFFFF)
#define D_MAX_DISTANCE_VAL (0xFFFFFFFF)

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

	// robot may be either in cleaning state or Return to Base or Charging on Docking station
	enum class State {
		CLEAN_CLEAN, // stay & clean as  current location is still dirty;
		CLEAN_MOVE, // move as part of clean algo
		RETURN,// return to docking station 
		DOCK,  // stay on Docking &CHARGE
		//MOVE,  // move to specific coordinate - over CLEANED! area
		FINISH //stay on Dock, return "finsihed" to simulation 
	};


}