#include <iostream>
#include "clueBoard.h"
using namespace std;

//this is the demo main for displaying the clue board. as a team we should work
//with the common resources, when available.
int main() {
	boardTile** boardArray = new boardTile * [25];
	for (int i = 0; i < 25; i++) {
		boardArray[i] = new boardTile[25];
	}
	clueBoard gameBoard(boardArray);



	delete [] boardArray;
}