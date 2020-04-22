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
		tileType = "Wall";
	}
	else if (type == "f") {
		occupied = false;
		room = false;
		passable = true;
		tileType = "Floor";
	}
	else {
		occupied = false;
		room = true;
		passable = true;
		tileType = "Room";
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
void boardTile::setCoor(int row, int col) {
	location = Point(row, col);
}

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

	return *this;
}

char boardTile::charTile() {
	return tileType[0];
}