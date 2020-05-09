#include <iostream>
#include <string>
#include "clueBoard.h"

const int SIZE = 25;

using namespace std;

clueBoard::clueBoard(boardTile** boardArray) {
	board = boardArray;
}
/*
void clueBoard::charBoard() {
	for (int r = 0; r < 27; r++) {
		for (int c = 0; c < 27; c++) {
			cout << board[r][c].charTile();
		}
		cout << endl;
	}
}
*/