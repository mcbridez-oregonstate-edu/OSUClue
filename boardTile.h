#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>
<<<<<<< HEAD
#include "Point.h"

=======

enum TILE_TYPE {Floor, Wall, Room};
>>>>>>> nguyen-pham

class boardTile {
private:

<<<<<<< HEAD
	std::string tileType;
	bool occupied;
	bool room;
	bool passable;
	Point location;
=======
	TILE_TYPE tileType;
	std::string roomName;
	bool occupied;
	bool room;
	bool door;
	
>>>>>>> nguyen-pham

public:

	boardTile();
	boardTile(std::string type, int row, int col);
	boardTile(std::string type);
	boardTile(const boardTile& other);//copy constructor
	//constructor

	//destructor

<<<<<<< HEAD
	//assignment
	boardTile& operator = (const boardTile& other);
	//declarations
	bool isOccupied();
	bool isRoom();
	bool isPassable();
	void setCoor(int row, int col);
	char charTile();
=======
	
	bool isOccupied();
	bool isRoom();
	bool hasDoor();
	
	std::string getName();
	void setOccupied(int);
	TILE_TYPE getTile_type();
>>>>>>> nguyen-pham
};
#endif