#include <iostream>
#include <string>
#include "Point.h"

class boardTile {
private:

	std::string type;
	bool occupied;
	bool room;
	Point location;

public:

	boardTile(std::string type);
	//constructor

	//destructor

	//assignment

	//declarations
	bool isOccupied();
	bool isRoom();
	

};
