/*******************************************************************************************************************
**	Descrition: Functions related to the board
********************************************************************************************************************/
#include "boardFunctions.hpp"
#include "token.hpp"
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using std::getline;
using std::ifstream;

/************************************************************************************
**	Name:bool isValidMove(boardTile current_space, boardTile target_space)
**	Description: Check if the tile being moved to is valid. Returns true if valid,
**				 false otherwise. Takes as arguments the boardTile of the current
**				 space and the space being moved to
************************************************************************************/
bool isValidMove(boardTile* current_space, boardTile* target_space, int& stepCount) {
	bool room_movement = 0;


	// check if space is occupied or not
	if (!target_space->isOccupied()) {

		// check if player is moving into/out of a room through a door
		if ((current_space->getTile_type() == Room && target_space->getTile_type() == Floor) || (current_space->getTile_type() == Floor && target_space->getTile_type() == Room)) {

			// check if both tiles are connected through a door
			if (current_space->hasDoor() && target_space->hasDoor()) {

				current_space->setOccupied(0);// set the space being left to unoccupied

				// set the target space to occupied if the user is moving out of room, and decrement step counter
				if (target_space->getTile_type() == Floor) {

					target_space->setOccupied(1);
					stepCount--;
				}
				// player is moving into a room which ends movement, does not occupy the space because multple tokens can be in the room
				else {
					stepCount = 0;
				}
				return true;
			}

			
		}
		// user is moving from floor->floor or room->room
		else {
			if (!(current_space->getTile_type() == Room && target_space->getTile_type() == Room)) {
				(stepCount)--;
				current_space->setOccupied(0); // set the space being left to unoccupied
				target_space->setOccupied(1); // set the target space to occupied if moving to a floor tile
			}
			else {
				current_space->setOccupied(0); // movement in room should not block other players
			}
			return true;
		}
	}

	// user cannot move through wall
	return false;

}


/************************************************************************************
**	Name:bool boardTile*** createBoardArray()
**	Description: Function that creates the logical tiles of the board. Returns a pointer
**				 to a 2D array of boardTiles representing the board
************************************************************************************/
boardTile*** createBoardArray() {
	boardTile*** boardArray = new boardTile * *[26];
	for (int i = 0; i < 26; i++) {
		boardArray[i] = new boardTile * [27];
	}


	//opening csv file to fill board data
	ifstream dataSource;
	dataSource.open("res/NewClueBoardCSV.csv");
	if (dataSource.fail()) {
		cout << "Failed to open csv." << endl;
		return 0;
	}
	string line, word, temp;
	int row = 0;
	int col = 0;

	//filling the board based on data from the CSV
	while (!dataSource.eof()) {
		string tempStringArray[24];
		col = 0;
		getline(dataSource, line);
		stringstream tempstream(line);
		while (getline(tempstream, word, ',')) {

			boardArray[row][col] = new boardTile(word, row, col);
			col++;
		}
		row++;
	}

	return boardArray;
}


/************************************************************************************
**	Name: vector<token*> playerTokens(int, int)
**	Description: Function that creates the player tokens. Returns a vector of tokens
**				 representing the player tokens. Takes two doubles representing the width and height
**				 of the tiles, and a 2D array of boardTiles representing the logical
**				 representation of the board
************************************************************************************/
vector<token*> playerTokens(double width, double height, boardTile*** boardArray) {

	//making mustard colored test piece
	token* mustard = new token("Colonel Mustard", width, height, boardArray);
	token* scarlett = new token("Miss Scarlet", width, height, boardArray);
	token* green = new token("Mr. Green", width, height, boardArray);
	token* plum = new token("Professor Plum", width, height, boardArray);
	token* peacock = new token("Mrs. Peacock", width, height, boardArray);
	token* white = new token("Mrs. White", width, height, boardArray);

	//making a container of players
	vector<token*>players;
	players.push_back(scarlett);
	players.push_back(mustard);
	players.push_back(green);
	players.push_back(plum);
	players.push_back(peacock);
	players.push_back(white);

	return players;
}