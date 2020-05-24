#include <iostream>
#include "boardTile.h"

using namespace std;

boardTile::boardTile(string type, int row, int col) {

	if (type.at(0) == 'w') {
		occupied = true;
		room = false;
		
		door = false;
		tileType = Wall;
	}
	else if (type.at(0) == 'f') {
		occupied = false;
		room = false;



		door = false;
		tileType = Floor;
	}
	else if (type.at(0) == 'r') {
		occupied = false;
		room = true;
		
		door = false;
		tileType = Room;
	}
	else if (type.at(0) == 'o') {
		occupied = false;
		room = false;


		door = true;

		tileType = Floor;
	}
	else {
		occupied = false;
		room = true;
		
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

	
	

	tileType = other.tileType;
	door = other.door;
}


boardTile::boardTile() {

	occupied = false;
	room = false;
	//passable = false;
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
}