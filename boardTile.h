#ifndef BOARDTILE_H
#define BOARDTILE_H
#include <iostream>
#include <string>

enum TILE_TYPE { Floor, Wall, Room };

class boardTile {
private:

	TILE_TYPE tileType;
	std::string roomName;
	bool occupied;
	bool room;
	bool door;


	int row;
	int col;


public:

	boardTile();
	boardTile(std::string type, int row, int col);
	boardTile(std::string type);
	boardTile(const boardTile& other);//copy constructor
	//constructor

	//destructor


	bool isOccupied();
	bool isRoom();
	bool hasDoor();

	std::string getName();
	void setOccupied(int);
	TILE_TYPE getTile_type();

	int getRow();
	int getCol();
};
#endif