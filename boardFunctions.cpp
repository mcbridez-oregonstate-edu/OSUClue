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

/************************************************************************************************
		void move(sf::Event* event, boardTile** boardArray, token* playerToken, int* steps)
 * Description: Takes an event and determines if the properties of the event warrant moving the
 * token, then moves the token as appropriate.
************************************************************************************************/
void move(sf::Event* event, boardTile*** boardArray, token* playerToken, int* steps)
{
	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;

	// Move token right
	if (event->key.code == sf::Keyboard::Right)
	{
		if (steps > 0) {
			if (isValidMove(playerToken->get_space(), boardArray[playerToken->get_row()][playerToken->get_col() + 1], *steps))
			{
				playerToken->get_space()->setOccupied(0);
				playerToken->move_token(width, 0, 0, 1, boardArray);
				playerToken->get_space()->setOccupied(1);
			}
		}
	}
	// move token left
	else if (event->key.code == sf::Keyboard::Left)
	{
		if (steps > 0) {
			if (isValidMove(playerToken->get_space(), boardArray[playerToken->get_row()][playerToken->get_col() - 1], *steps))
			{
				playerToken->get_space()->setOccupied(0);
				playerToken->move_token(-width, 0, 0, -1, boardArray);
				playerToken->get_space()->setOccupied(1);
			}
		}
	}
	// move token down
	else if (event->key.code == sf::Keyboard::Down)
	{
		if (steps > 0) {
			if (isValidMove(playerToken->get_space(), boardArray[playerToken->get_row() + 1][playerToken->get_col()], *steps))
			{
				playerToken->get_space()->setOccupied(0);
				playerToken->move_token(0, height, 1, 0, boardArray);
				playerToken->get_space()->setOccupied(1);
			}
		}
	}
	//move token up
	else if (event->key.code == sf::Keyboard::Up)
	{
		if (steps > 0) {
			if (isValidMove(playerToken->get_space(), boardArray[playerToken->get_row() - 1][playerToken->get_col()], *steps))
			{
				playerToken->get_space()->setOccupied(0);
				playerToken->move_token(0, -height, -1, 0, boardArray);
				playerToken->get_space()->setOccupied(1);
			}
		}
	}
}

/************************************************************************************
**	Name: vector<CardButton> createButtonArray(int);
**	Description: Function that creates and returns a vector containing the buttons for
**				 the cards. Takes an int which signals which set of buttons to make:
**				 0 = people, 1 = weapons, 2 = locations
************************************************************************************/
vector<CardButton*> createButtonArray(int type)
{

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
		NotebookButton* button = new NotebookButton(i, sf::Vector2f(1200, 200 + (20 * i)));
		buttonVector.push_back(button);
	}

	return buttonVector;
}

vector<sf::Text> createNotebookLabels(sf::Font* font)
{
	vector<sf::Text> notebookLabels;
	for (int i = 0; i < 21; i++)
	{
		sf::Text text;
		text.setFont(*font);
		notebookLabels.push_back(text);
		notebookLabels[i].setCharacterSize(20);
		notebookLabels[i].setPosition(sf::Vector2f(1000, 190 + (20 * i)));
	}

	notebookLabels[0].setString("Miss Scarlet:");
	notebookLabels[1].setString("Colonel Mustard:");
	notebookLabels[2].setString("Mrs. White:");
	notebookLabels[3].setString("Mr. Green:");
	notebookLabels[4].setString("Mrs. Peacock:");
	notebookLabels[5].setString("Prof. Plum:");

	notebookLabels[6].setString("Wrench:");
	notebookLabels[7].setString("Revolver:");
	notebookLabels[8].setString("Lead Pipe:");
	notebookLabels[9].setString("Rope:");
	notebookLabels[10].setString("Candlestick:");
	notebookLabels[11].setString("Knife:");

	notebookLabels[12].setString("Conservatory:");
	notebookLabels[13].setString("Lounge:");
	notebookLabels[14].setString("Billiard Room:");
	notebookLabels[15].setString("Library:");
	notebookLabels[16].setString("Dining Room:");
	notebookLabels[17].setString("Hall:");
	notebookLabels[18].setString("Ballroom:");
	notebookLabels[19].setString("Kitchen:");
	notebookLabels[20].setString("Study:");

	return notebookLabels;
}

/************************************************************************************
**	Name: int secretPassage(boardTile* current_space, boardTile*** board);
**	Description: Function that implements secret passages. Returns 1 if a secret passage
**				 is used, and 0 otherwise.
************************************************************************************/
int secretPassage(token* token, boardTile*** board) {

	if (token->get_space()->getName() == "Kitchen") {

		token->move_passage(824.5, 225, 4, 23, board);

		return 1;
	}
	else if (token->get_space()->getName() == "Study") {
		token->move_passage(449.25, 585, 22, 4, board);
		return 1;
	}
	else if (token->get_space()->getName() == "Lounge") {

		token->move_passage(449.25, 205, 3, 4, board);;

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

/************************************************************************************
**	Name: void moveSuggestion(std::string room,token* token, boardTile*** board);
**	Description: Function that moves the token to the specified room due to a suggestion
************************************************************************************/
void moveSuggestion(std::string room, token* token, boardTile*** board)
{
	if (room == "Lounge") {
		token->move_passage(804.75, 565, 21, 22, board);
	}
	else if (room == "Dining Room") {
		token->move_passage(627, 545, 20, 13, board);
	}
	else if (room == "Conservatory") {
		token->move_passage(449.25, 205, 3, 4, board);
	}
	else if (room == "Billiard Room") {
		token->move_passage(587.5, 225, 4, 11, board);
	}
	else if (room == "Library") {
		token->move_passage(706, 225, 4, 17, board);
	}
	else if (room == "Study") {
		token->move_passage(824.6, 225, 4, 23, board);
	}
	else if (room == "Ballroom") {
		token->move_passage(469, 405, 13, 5, board);
	}
	else if (room == "Hall") {
		token->move_passage(804.75, 385, 12, 22, board);
	}
	else if (room == "Kitchen") {
		token->move_passage(449.25, 205, 22, 4, board);
	}
}

/******************************************************************************************************************
									bool checkDoors(boardTile*** board, string roomName)
 * Description: Takes a board and the name of the room to check, then checks the appropriate door spaces to see
 * if they are all blocked (occupied) by another token. If all the doors are blocked, returns true, else returns
 * false
******************************************************************************************************************/
bool checkDoors(boardTile*** board, string roomName)
{
	bool blocked = false;

	if (roomName == "Lounge")
	{
		if (board[20][19]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Dining Room")
	{
		if (board[18][19]->isOccupied() && board[14][17]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Conservatory")
	{
		if (board[7][9]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Billiard Room")
	{
		if (board[11][8]->isOccupied() && board[15][3]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Library")
	{
		if (board[15][5]->isOccupied() && board[18][9]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Study")
	{
		if (board[22][8]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Ballroom")
	{
		if (board[7][18]->isOccupied() && board[10][16]->isOccupied() && board[10][11]->isOccupied() && board[7][9]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Hall")
	{
		if (board[22][10]->isOccupied() && board[19][13]->isOccupied() && board[19][14]->isOccupied())
		{
			blocked = true;
		}
	}
	else if (roomName == "Kitchen")
	{
		if (board[9][21]->isOccupied())
		{
			blocked = true;
		}
	}

	return blocked;
}

/**************************************************************************************************
									bool isSecretPassage(token* token)
 * Description: Checks if the token's current space is a secret passage
**************************************************************************************************/
bool isSecretPassage(token* token)
{
	bool isPassage = false;
	if (token->get_space()->getName() == "Conservatory" || token->get_space()->getName() == "Kitchen" ||
		token->get_space()->getName() == "Study" || token->get_space()->getName() == "Lounge")
	{
		isPassage = true;
	}

	return isPassage;
}