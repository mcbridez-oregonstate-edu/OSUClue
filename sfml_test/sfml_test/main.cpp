#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include "token.hpp"
#include "boardTile.h"
#include "boardFunctions.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;

//bool isValidMove(boardTile* current_space, boardTile* target_space, int& stepCount);

int main()
{
	//random seed
	srand(time(0));


	//graphical output section
	//creating a render window with SFML
	sf::RenderWindow window(sf::VideoMode(810, 810), "Clue!", sf::Style::Default);

	
	// create the logical tiles of the board
	boardTile*** boardArray = createBoardArray();


	// create the visual representation of the board
	sf::Texture board_texture;
	if (!board_texture.loadFromFile("res/images/clueboard.png", sf::IntRect(0, 0, 500, 487)))
	{
		cout << "Cannot open clueboard.png" << endl;
	}



	sf::Sprite rendered_board;
	rendered_board.move(sf::Vector2f(155, 161.5));
	rendered_board.setTexture(board_texture);

	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;

	

	vector<token*> players = playerTokens(width, height, boardArray);

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
			system("cls");
			std::cout << "Player " << current_player + 1 << " rolled a " << die_1 << " and a " << die_2 << std::endl;
			std::cout << "They can move " << steps << " spaces" << std::endl;
			std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;
			has_rolled = 1;
		}

		stepCounterString = "Player " + std::to_string(current_player + 1) +
			"\nSteps: " + std::to_string(steps) +
			"\nLocation: " + players[current_player]->get_space()->getName();
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
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row()][players[current_player]->get_col() + 1], steps)) {
								
								players[current_player]->move_token(width, 0, 0, 1, boardArray);
							
															
							}
						}

						break;
					}

					//move a piece left
					if (event.key.code == sf::Keyboard::Left)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row()][players[current_player]->get_col() - 1], steps)) {
							
								players[current_player]->move_token(-width, 0, 0, -1, boardArray);
							
								
								
							}
						}

						break;
					}

					//movve a piece down
					if (event.key.code == sf::Keyboard::Down)
					{

						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row() + 1][players[current_player]->get_col()], steps)) {
								
								players[current_player]->move_token(0, height, 1, 0, boardArray);
								
							
								
							}
						}
						break;
					}

					//move a piece up
					if (event.key.code == sf::Keyboard::Up)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->get_space(), boardArray[players[current_player]->get_row() - 1][players[current_player]->get_col()], steps)) {
							
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

		for (int i = 0; i < players.size(); i++) {
			window.draw(players[i]->get_token());
		}

		
		/*window.draw(mustard.get_token());
		window.draw(scarlett.get_token());
		window.draw(green.get_token());
		window.draw(plum.get_token());
		window.draw(peacock.get_token());
		window.draw(white.get_token());*/
		window.draw(stepCounterText);
		window.display();

	}
	// free allocated memory


	for (int i = 0; i < 26; i++) {

		for (int j = 0; j < 27; j++) {
			delete boardArray[i][j];
		}
		delete[] boardArray[i];
	}
	delete[] boardArray;

	for (int i = 0; i < players.size(); i++) {
		delete players[i];
	}
	return 0;
}


///************************************************************************************
//**	Name:bool isValidMove(boardTile current_space, boardTile target_space)
//**	Description: Check if the tile being moved to is valid. Returns true if valid,
//**				 false otherwise. Takes as arguments the boardTile of the current
//**				 space and the space being moved to
//************************************************************************************/
//bool isValidMove(boardTile* current_space, boardTile* target_space, int& stepCount) {
//	bool room_movement = 0;
//
//	if (current_space->getTile_type() == Room && target_space->getTile_type() == Room) {
//		room_movement = 1;
//		
//	}
//
//	if (target_space->isOccupied())
//	{
//		return false;
//	}
//
//	
//	if (target_space->isPassable()) {
//
//		// player is moving between floor and room
//		if ((current_space->getTile_type() == Room && target_space->getTile_type() == Floor) || (current_space->getTile_type() == Floor && target_space->getTile_type() == Room)) {
//
//
//			if (current_space->hasDoor() && target_space->hasDoor()) {
//				
//				current_space->setOccupied(0);// set the space being left to unoccupied
//
//				// set the target space to occupied if the user is moving out of room
//				if (target_space->getTile_type() == Floor){
//					
//					target_space->setOccupied(1);
//					stepCount--;
//				}
//				else { // player is moving into a room which ends movement
//					stepCount = 0;
//				}
//				return true;
//			}
//
//			// floor and/or room tile does not have a door to pass through
//			else {
//				
//				return false;
//			}
//		}
//			// user is moving from floor->floor or room->room
//		else {
//			if (!room_movement) {
//				(stepCount)--;
//				current_space->setOccupied(0); // set the space being left to unoccupied
//				target_space->setOccupied(1); // set the target space to occupied if moving to a floor tile
//			}
//			else {
//				current_space->setOccupied(0); // movement in room should not block other players
//			}
//			return true;
//		}
//	}
//	// user cannot move through wall
//	else {
//		return false;
//	}
//
//}
//
