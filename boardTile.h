#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>
#include "Point.h"


class boardTile {
private:

	std::string tileType;
	bool occupied;
	bool room;
	bool passable;
	Point location;

public:

	boardTile();
	boardTile(std::string type, int row, int col);
	boardTile(std::string type);
	boardTile(const boardTile& other);//copy constructor
	//constructor

	//destructor

	//assignment
	boardTile& operator = (const boardTile& other);
	//declarations
	bool isOccupied();
	bool isRoom();
	bool isPassable();
	void setCoor(int row, int col);
	char charTile();
};
#endif