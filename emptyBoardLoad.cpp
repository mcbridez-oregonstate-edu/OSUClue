#include <iostream>
#include "clueBoard.h"
using namespace std;

//this is the demo main for creation of a blank board
int main() {
	boardTile** boardArray = new boardTile * [25];
	for (int i = 0; i < 25; i++) {
		boardArray[i] = new boardTile[25];
	}
	clueBoard gameBoard(boardArray);



	delete [] boardArray;
}