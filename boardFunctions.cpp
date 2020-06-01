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
bool isValidMove(Player* current_player, boardTile* target_space, int& stepCount) {
	bool room_movement = 0;
	boardTile* current_space = current_player->getToken()->get_space();

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
					current_player->setSuggested(0); // if player moves out of the room, they are allowed to make a suggetion when moving into a room
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


/************************************************************************************
**	Name: vector<CardButton> createButtonArray(int);
**	Description: Function that creates and returns a vector containing the buttons for
**				 the cards. Takes an int which signals which set of buttons to make:
**				 0 = people, 1 = weapons, 2 = locations
************************************************************************************/
vector<CardButton*> createButtonArray(int type) {
	
	vector<CardButton*> buttonVector;

	// poeple buttons
	if (type == 0) {
		CardButton* b_scarlet = new CardButton("Miss Scarlet", sf::Vector2f(375, 140));
		CardButton* b_green = new CardButton("Mr. Green", sf::Vector2f(575, 140));
		CardButton* b_mustard = new CardButton("Colonel Mustard", sf::Vector2f(775, 140));
		CardButton* b_white = new CardButton("Mrs. White", sf::Vector2f(375, 480));
		CardButton* b_peacock = new CardButton("Mrs. Peacock", sf::Vector2f(575, 480));
		CardButton* b_plum = new CardButton("Professor Plum", sf::Vector2f(775, 480));

		buttonVector.push_back(b_scarlet);
		buttonVector.push_back(b_green);
		buttonVector.push_back(b_mustard);
		buttonVector.push_back(b_white);
		buttonVector.push_back(b_peacock);
		buttonVector.push_back(b_plum);
	}
	// weapon buttons
	else if (type == 1) {
		CardButton* b_rope = new CardButton("Rope", sf::Vector2f(375, 140));
		CardButton* b_wrench = new CardButton("Wrench", sf::Vector2f(575, 140));
		CardButton* b_pipe = new CardButton("Lead Pipe", sf::Vector2f(775, 140));
		CardButton* b_knife = new CardButton("Knife", sf::Vector2f(375, 480));
		CardButton* b_candlestick = new CardButton("Candlestick", sf::Vector2f(575, 480));
		CardButton* b_revolver = new CardButton("Revolver", sf::Vector2f(775, 480));

		buttonVector.push_back(b_rope);
		buttonVector.push_back(b_wrench);
		buttonVector.push_back(b_pipe);
		buttonVector.push_back(b_knife);
		buttonVector.push_back(b_candlestick);
		buttonVector.push_back(b_revolver);
	}
	// location buttons
	else if (type == 2) {
		CardButton* b_lounge = new CardButton("Lounge", sf::Vector2f(375, 80));
		CardButton* b_library = new CardButton("Library", sf::Vector2f(575, 80));
		CardButton* b_ballroom = new CardButton("Ballroom", sf::Vector2f(775, 80));
		CardButton* b_billiard = new CardButton("Billiard Room", sf::Vector2f(375, 380));
		CardButton* b_kitchen = new CardButton("Kitchen", sf::Vector2f(575, 380));
		CardButton* b_conservatory = new CardButton("Conservatory", sf::Vector2f(775, 380));
		CardButton* b_hall = new CardButton("Hall", sf::Vector2f(375, 680));
		CardButton* b_study = new CardButton("Study", sf::Vector2f(575, 680));
		CardButton* b_dining = new CardButton("Dining Room", sf::Vector2f(775, 680));

		buttonVector.push_back(b_lounge);
		buttonVector.push_back(b_library);
		buttonVector.push_back(b_ballroom);
		buttonVector.push_back(b_billiard);
		buttonVector.push_back(b_kitchen);
		buttonVector.push_back(b_conservatory);
		buttonVector.push_back(b_hall);
		buttonVector.push_back(b_study);
		buttonVector.push_back(b_dining);

	}

	return buttonVector;
}


/************************************************************************************
**	Name:vector<NotebookButton*> createNotebookButtons()
**	Description: Function that creates and returns a vector containing the buttons for
				 the notebook
************************************************************************************/
vector<NotebookButton*> createNotebookButtons()
{

	vector<NotebookButton*> buttonVector;

	for (int i = 0; i < 21; i++) {
		NotebookButton* button = new NotebookButton(i, sf::Vector2f(1100, 10 + (18 * i)));
		buttonVector.push_back(button);
	}

	return buttonVector;
}

/************************************************************************************
**	Name: int secretPassage(boardTile* current_space, boardTile*** board);
**	Description: Function that implements secret passages. Returns 1 if a secret passage
**				 is used, and 0 otherwise.
************************************************************************************/
int secretPassage(token* token, boardTile*** board){

	if (token->get_space()->getName() == "Kitchen") {

		token->move_passage(824.5, 225, 4, 23, board);

		return 1;
	}
	else if (token->get_space()->getName() == "Study") {
		token->move_passage(449.25, 585, 22, 4, board);
		return 1;
	}
	else if (token->get_space()->getName() == "Lounge") {
		token->move_passage(449.25, 205, 3, 4, board);
		return 1;
	}
	else if (token->get_space()->getName() == "Conservatory") {
		token->move_passage(804.75, 565, 21, 22, board);
		return 1;
	}
	else {
		return 0;
	}
}
