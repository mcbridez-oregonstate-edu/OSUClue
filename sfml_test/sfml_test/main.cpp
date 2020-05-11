#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include "clueBoard.h"
#include "token.hpp"

#include <stdlib.h>
#include <time.h>

using namespace std;
void writeToLog(string message, string variable);
bool isValidMove(boardTile current_space, boardTile target_space);
int main()
{
//graphical output section
	//creating a render window with SFML
	sf::RenderWindow window(sf::VideoMode(810, 810), "Clue!", sf::Style::Default);

	//making a matrix representing the board
	boardTile** boardArray = new boardTile * [26];
	for (int i = 0; i < 26; i++) {
		boardArray[i] = new boardTile[27];
	}


	//opening csv file to fill board data
	ifstream dataSource;
	dataSource.open("NewClueBoardCSV.csv");
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
			boardTile tempTile(word, row, col);
			writeToLog("Grabbed tile type:", word);
			boardArray[row][col] = tempTile;
			col++;
		}
		row++;
	}


	sf::Texture board_texture;
	if (!board_texture.loadFromFile("clueboard.png", sf::IntRect(0, 0, 500, 487)))
	{
		cout << "Cannot open clueboard.png" << endl;
	}



	sf::Sprite rendered_board;
	rendered_board.move(sf::Vector2f(155, 161.5));
	rendered_board.setTexture(board_texture);


	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;

	//making mustard colored test piece
	token mustard("mustard", width, height);
	token scarlett("scarlett", width, height);
	token green("green", width, height);
	token plum("plum", width, height);
	token peacock("peacock", width, height);
	token white("white", width, height);

	//making a container of players
	vector<token*>players;
	players.push_back(&scarlett);
	players.push_back(&mustard);
	players.push_back(&green);
	players.push_back(&plum);
	players.push_back(&peacock);
	players.push_back(&white);

	//control variables for changing player control
	int current_player = 0;
	int num_players = players.size() - 1;

	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				//move a piece right
				if (event.key.code == sf::Keyboard::Right)
				{
					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row()][players[current_player]->get_col() + 1])) {
						players[current_player]->move_token(width, 0, 0, 1);
					}

					break;
				}

				//move a piece left
				if (event.key.code == sf::Keyboard::Left)
				{

					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row()][players[current_player]->get_col() - 1])) {
						players[current_player]->move_token(-width, 0, 0, -1);

					}

					break;
				}

				//movve a piece down
				if (event.key.code == sf::Keyboard::Down)
				{


					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()], boardArray[players[current_player]->get_row() + 1][players[current_player]->get_col()])) {
						players[current_player]->move_token(0, height, 1, 0);

					}

					break;
				}

				//move a piece up
				if (event.key.code == sf::Keyboard::Up)
				{

					if (isValidMove(boardArray[players[current_player]->get_row()][players[current_player]->get_col()],
						boardArray[players[current_player]->get_row() - 1][players[current_player]->get_col()])) {
						players[current_player]->move_token(0, -height, -1, 0);

					}

					break;
				}

				//change player control
				if (event.key.code == sf::Keyboard::Enter)
				{


					current_player++;

					if (current_player > num_players)
					{
						current_player = 0;

					}
				}

				break;

			default:
				break;
			}

		
		}

		window.clear();

		window.draw(rendered_board);
		window.draw(mustard.get_token());
		window.draw(scarlett.get_token());
		window.draw(green.get_token());
		window.draw(plum.get_token());
		window.draw(peacock.get_token());
		window.draw(white.get_token());
		window.display();
	}

	// free allocated memory

		

	
		


	for (int i = 0; i < 26; i++) {
		delete[] boardArray[i];
	}
	delete[] boardArray;
	return 0;
}

void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
}

/************************************************************************************
**	Name:bool isValidMove(boardTile current_space, boardTile target_space)
**	Description: Check if the tile being moved to is valid. Returns true if valid,
**				 false otherwise. Takes as arguments the boardTile of the current
**				 space and the space being moved to
************************************************************************************/
bool isValidMove(boardTile current_space, boardTile target_space) {

	if (target_space.isOccupied())
	{
		return false;
	}

	if (target_space.isPassable()) {
		if ((current_space.getTile_type() == Room && target_space.getTile_type() == Floor) || (current_space.getTile_type() == Floor && target_space.getTile_type() == Room)) {


			if (current_space.hasDoor() && target_space.hasDoor()) {

				return true;
			}
				// hall and/or room tile does not have a door to pass through
			else {

				return false;
			}
		}
			// user is moving from hall->hall or room->room
		else {
			return true;
		}
	}
	// user cannot move through wall
	else {
		return false;
	}

}