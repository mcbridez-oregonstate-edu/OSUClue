#include <iostream>
<<<<<<< HEAD
#include "Point.h"
=======
>>>>>>> nguyen-pham
#include "boardTile.h"

using namespace std;

boardTile::boardTile(string type, int row, int col) {
<<<<<<< HEAD
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
=======
	
	if (type.at(0) == 'w') {
		occupied = true;
		room = false;
		//passable = false;
		door = false;
		tileType = Wall;
	}
	else if (type.at(0) == 'f') {
		occupied = false;
		room = false;
	//	passable = true;
		door = false;
		tileType = Floor;
	}
	else if (type.at(0) == 'r') {
		occupied = false;
		room = true;
		//passable = true;
		door = false;
		tileType = Room;
	}
	else if (type.at(0) == 'o') {
		occupied = false;
		room = false;
	//	passable = true;
		door = true;
		
		tileType = Floor;
>>>>>>> nguyen-pham
	}
	else {
		occupied = false;
		room = true;
<<<<<<< HEAD
		passable = true;
		tileType = "Room";
=======
		//passable = true;
		door = true;
		tileType = Room;
	}

	// set tile names
	if (type.at(1) == 'c') {
		roomName = "Conservatory";
	}
	else if (type.at(1) == 'p') {
		roomName = "Billiard Room";
	}
	else if (type.at(1) == 'l') {
		roomName = "Library";
	}
	else if (type.at(1) == 's') {
		roomName = "Study";
	}
	else if (type.at(1) == 'b') {
		roomName = "Ballroom";
	}
	else if (type.at(1) == 'h') {
		roomName = "Hall";
	}
	else if (type.at(1) == 'k') {
		roomName = "Kitchen";
	}
	else if (type.at(1) == 'd') {
		roomName = "Dining Room";
	}
	else if (type.at(1) == 'L') {
		roomName = "Lounge";
	}
	else {
		roomName = "Ground Floor";
>>>>>>> nguyen-pham
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
<<<<<<< HEAD
	passable = other.passable;
	location = other.location;
	tileType = other.tileType;
=======
	//passable = other.passable;
	
	tileType = other.tileType;
	door = other.door;
>>>>>>> nguyen-pham
}


boardTile::boardTile() {
<<<<<<< HEAD
	location = Point(0, 0);
	occupied = false;
	room = false;
	passable = false;
=======
	
	occupied = false;
	room = false;
	//passable = false;
>>>>>>> nguyen-pham
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
<<<<<<< HEAD
=======
/*
>>>>>>> nguyen-pham
bool boardTile::isPassable() {
	if (passable) {
		return true;
	}
	else {
		return false;
	}
}
<<<<<<< HEAD
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
=======
*/
bool boardTile::hasDoor() {

	if (door == true) {
		return true;
	}
	else {
		return false;
	}
}



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

/*******************************************************************************************************************
**	Name: string getName()
**	Descrition: Returns the name of the room
********************************************************************************************************************/
std::string boardTile::getName() {
	return roomName;
>>>>>>> nguyen-pham
}