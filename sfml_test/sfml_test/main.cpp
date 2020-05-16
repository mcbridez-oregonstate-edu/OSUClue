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
bool isValidMove(boardTile current_space, boardTile target_space, int* stepCount);
bool isRoom(boardTile current_space);
int main()
{
	//random seed
	srand(time(0));


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
	token mustard("mustard", width, height, boardArray);
	token scarlett("scarlett", width, height, boardArray);
	token green("green", width, height, boardArray);
	token plum("plum", width, height, boardArray);
	token peacock("peacock", width, height, boardArray);
	token white("white", width, height, boardArray);

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

	//player step count for moving
	int steps;
	bool has_rolled = 0;
	bool move_state = 1;

	//making text for step counter
	sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}
	sf::Text stepCounterText;
	string stepCounterString;
	stepCounterText.setFont(font);
	
	

	// game loop
	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;

		if (!has_rolled) {
			int die_1 = (rand() % 6) + 1;
			int die_2 = (rand() % 6) + 1;
			steps = die_1 + die_2;
			std::cout << "Player " << current_player + 1 << " rolled a " << die_1 << " and a " << die_2 << std::endl;
			std::cout << "They can move " << steps << " spaces" << std::endl;
			std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;
			has_rolled = 1;
		}

		stepCounterString = "Player " + std::to_string(current_player + 1) + "\n Steps: " + std::to_string(steps);
		stepCounterText.setString(stepCounterString);
		while (window.pollEvent(event))
		{
		
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (move_state) {
					//move a piece right
					if (event.key.code == sf::Keyboard::Right)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row()][players[current_player]->get_col() + 1], &steps)) {
								players[current_player]->move_token(width, 0, 0, 1, boardArray);
								
								// decrement step counter only if player has moved into 
								if (!isRoom(players[current_player]->get_space())) {
									
								}
								
							}
						}

						break;
					}

					//move a piece left
					if (event.key.code == sf::Keyboard::Left)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row()][players[current_player]->get_col() - 1], &steps)) {
								players[current_player]->move_token(-width, 0, 0, -1, boardArray);
								
								
							}
						}

						break;
					}

					//movve a piece down
					if (event.key.code == sf::Keyboard::Down)
					{

						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row() + 1][players[current_player]->get_col()], &steps)) {
								players[current_player]->move_token(0, height, 1, 0, boardArray);
							
								
							}
						}
						break;
					}

					//move a piece up
					if (event.key.code == sf::Keyboard::Up)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row() - 1][players[current_player]->get_col()], &steps)) {
								players[current_player]->move_token(0, -height, -1, 0, boardArray);
								
							}
						}
						break;
					}

					//change player control
					if (event.key.code == sf::Keyboard::Enter)
					{


						current_player++;
						has_rolled = 0;

						if (current_player > num_players)
						{
							current_player = 0;

						}
					}

					break;
				}
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
		window.draw(stepCounterText);
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
bool isValidMove(boardTile current_space, boardTile target_space, int* stepCount) {
	bool room_movement = 0; 

	if (current_space.getTile_type() == Room && target_space.getTile_type() == Room) {
		room_movement = 1;
	}

	if (target_space.isOccupied())
	{
		return false;
	}


	if (target_space.isPassable()) {
		if ((current_space.getTile_type() == Room && target_space.getTile_type() == Floor) || (current_space.getTile_type() == Floor && target_space.getTile_type() == Room)) {


			if (current_space.hasDoor() && target_space.hasDoor()) {

				if (!room_movement) {
					(*stepCount)--;
				}
				return true;
			}
				// hall and/or room tile does not have a door to pass through
			else {
				
				return false;
			}
		}
			// user is moving from hall->hall or room->room
		else {
			if (!room_movement) {
				(*stepCount)--;
			}
			return true;
		}
	}
	// user cannot move through wall
	else {
		return false;
	}

}

/************************************************************************************
**	Name:bool isRooom(boardTile current_space)
**	Description: Check if the tile the token is on is a room tile or not. Returns 1 if
**				 the tile is a room, and 0 otherwise.
************************************************************************************/
bool isRoom(boardTile current_space) {
	return current_space.isRoom();
}