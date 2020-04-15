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
	}
	else if (type == "f") {
		occupied = false;
		room = false;
		passable = true;
	}
	else {
		occupied = false;
		room = true;
		passable = true;
	}
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
