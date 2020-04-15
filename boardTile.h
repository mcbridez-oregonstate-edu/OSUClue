#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>
#include "Point.h"


class boardTile {
private:

	std::string type;
	bool occupied;
	bool room;
	bool passable;
	Point location;

public:

	boardTile();
	boardTile(std::string type, int row, int col);
	//constructor

	//destructor

	//assignment

	//declarations
	bool isOccupied();
	bool isRoom();
	

};
#endif