#include <iostream>
#include "Point.h"
#include "boardTile.h"

using namespace std;

boardTile::boardTile(string type, int row, int col) {
	location = Point(row, col);
	if (type == "w") {
		occupied = false;
		room = false;
		passable = false;
		door = false;
		tileType = Wall;
	}
	else if (type == "f") {
		occupied = false;
		room = false;
		passable = true;
		door = false;
		tileType = Floor;
	}
	else if (type == "r") {
		occupied = false;
		room = true;
		passable = true;
		door = false;
		tileType = Room;
	}
	else if (type == "o") {
		occupied = false;
		room = false;
		passable = true;
		door = true;
		
		tileType = Floor;
	}
	else {
		occupied = false;
		room = true;
		passable = true;
		door = true;
	
		tileType = Room;
	}
}
boardTile::boardTile(std::string type)
{
}

//copy constructor
boardTile::boardTile(const boardTile& other)
{
	occupied = other.occupied;
	room = other.room;
	passable = other.passable;
	location = other.location;
	tileType = other.tileType;
	door = other.door;
}


boardTile::boardTile() {
	location = Point(0, 0);
	occupied = false;
	room = false;
	passable = false;
}
bool boardTile::isOccupied() {
	if (occupied == true) {
		return true;
	}
	else {
		return false;
	}
}
bool boardTile::isRoom() {
	if (room == true) {
		return true;
	}
	else {
		return false;
	}
}
bool boardTile::isPassable() {
	if (passable) {
		return true;
	}
	else {
		return false;
	}
}

bool boardTile::hasDoor() {

	if (door == true) {
		return true;
	}
	else {
		return false;
	}
}

void boardTile::setCoor(int row, int col) {
	location = Point(row, col);
}
/*
boardTile& boardTile::operator = (const boardTile& other) {
	if (this == &other)
	{
		return *this;
	}

	occupied = other.occupied;
	room = other.room;
	passable = other.passable;
	location = other.location;
	tileType = other.tileType;
	door = other.door;

	return *this;
}
*/
TILE_TYPE boardTile::getTile_type() {
	return tileType;
}

/*******************************************************************************************************************
**	Name: setOccupied(int choice)
**	Descrition:  Sets the tile to either occupied or unoccupied
********************************************************************************************************************/
void boardTile::setOccupied(int choice) {
	if (choice == 1) {
		occupied = true;
	}
	else {
		occupied = false;
	}

}