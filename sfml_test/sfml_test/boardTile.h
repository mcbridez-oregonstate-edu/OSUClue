#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>

enum TILE_TYPE {Floor, Wall, Room};

class boardTile {
private:

	TILE_TYPE tileType;
	bool occupied;
	bool room;
	bool passable;
	bool door;
	

public:

	boardTile();
	boardTile(std::string type, int row, int col);
	boardTile(std::string type);
	boardTile(const boardTile& other);//copy constructor
	//constructor

	//destructor

	
	bool isOccupied();
	bool isRoom();
	bool isPassable();
	bool hasDoor();
	
	void setOccupied(int);
	TILE_TYPE getTile_type();
};
#endif