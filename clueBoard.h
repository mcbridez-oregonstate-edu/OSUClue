#ifndef CLUEBOARD_H
#define CLUEBOARD_H
#include <iostream>
#include <string>
#include "boardTile.h"


class clueBoard {
private:
	const int length = 27;
	boardTile **board = nullptr;

public:

	//constructor
	clueBoard(boardTile**);
	//destructor

	//assignment

	//declarations
	void charBoard();
};
#endif