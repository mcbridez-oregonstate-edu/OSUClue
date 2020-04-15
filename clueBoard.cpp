#include <iostream>
#include <string>
#include "clueBoard.h"

const int SIZE = 25;

using namespace std;

clueBoard::clueBoard(boardTile** boardArray) {
	board = boardArray;
}