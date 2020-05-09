#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>
#include "Point.h"

enum TILE_TYPE {Floor, Wall, Room};

class boardTile {
private:

	TILE_TYPE tileType;
	bool occupied;
	bool room;
	bool passable;
	bool door;
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
	bool hasDoor();
	void setCoor(int row, int col);
	TILE_TYPE getTile_type();
};
#endif