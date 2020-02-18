#pragma once
class HouseInterface
{
	HouseInterface();
public:
	bool isClean();
	bool isWall(Direction d);
	bool isDirty();
	void moveRobot(Direction d);

};

