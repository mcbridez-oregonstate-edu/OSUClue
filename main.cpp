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


#include "player.hpp"
#include "deck.hpp"
//#include "game.hpp"
#include <iomanip>



using namespace std;
using std::tuple;


int main()
{
	//random seed
	srand(time(0));


	
	//creating a render window with SFML
	sf::RenderWindow window(sf::VideoMode(1280, 960), "Clue!", sf::Style::Default);


	// create the logical tiles of the board
	boardTile*** boardArray = createBoardArray();


	// create the visual representation of the board
	sf::Texture board_texture;
	if (!board_texture.loadFromFile("res/images/clueboard.png", sf::IntRect(0, 0, 500, 487)))
	{
		cout << "Cannot open clueboard.png" << endl;
	}

	sf::Sprite rendered_board;
	
	rendered_board.move(sf::Vector2f(390, 161.5));
	rendered_board.setTexture(board_texture);

	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;


	// create the player tokens
	vector<token*> tokensVect = playerTokens(width, height, boardArray);
	// [Scarlet, Mustard, Green, Plum, Peacock, White]


	// Creating Players
	
	//notebooks
	tuple<int, int> pos1;
	tuple<int, int> pos2;
	tuple<int, int> pos3;
	tuple<int, int> pos4;
	tuple<int, int> pos5;
	tuple<int, int> pos6;


	Player* player1 = new Player("Player 1 (Miss Scarlet)", tokensVect[0], pos1);
	Player* player2 = new Player("Player 2 (Colonel Mustard)", tokensVect[1], pos2);
	Player* player3 = new Player("Player 3 (Mr. Green)", tokensVect[2], pos3);
	Player* player4 = new Player("Player 4 (Professor Plum)", tokensVect[3], pos4);
	Player* player5 = new Player("Player 5 (Mrs. Peacock)", tokensVect[4], pos5);
	Player* player6 = new Player("Player 6 (Mrs. White)", tokensVect[5], pos6);

	vector<Player*> players = {player1, player2, player3, player4, player5, player6};


	// creating cards
	Deck newDeck;

	vector<Card*> solution = newDeck.getSolution();
	cout << "Suspect: " << solution[0]->getName() << endl;
	cout << "Weapon: " << solution[1]->getName() << endl;
	cout << "Room: " << solution[2]->getName() << endl;

	newDeck.shuffle();
	newDeck.deal(players);

	// for each card in player hand, set card position for display
	for (int i = 0; i < 6; i++) {

		
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				players[i]->getHand()[j]->setCardPos(sf::Vector2f(375, 680));
			}
			else if (j == 1) {
				players[i]->getHand()[j]->setCardPos(sf::Vector2f(575, 680));
			}
			else if (j == 2) {
				players[i]->getHand()[j]->setCardPos(sf::Vector2f(775, 680));
			}
		}

	}

	// printing out player hands
	for (int i = 0; i < players.size(); i++) {
		for (int j = 0; j < players[i]->getHand().size(); j++) {
			cout << players[i]->getName() << " has " << players[i]->getHand()[j]->getName() << endl;
		}
		cout << endl;
	}

	//control variables for changing player control
	int current_player = 0;
	int num_players = players.size() - 1;

	//player step count for moving
	int steps;
	bool has_rolled = 0;

	// game state control variable,  1 = move state, 0 = suggestion state
	bool game_state = 1;
	

	//making text box for player/step counter
	sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}
	sf::Text stepCounterText;
	string stepCounterString;
	stepCounterText.setFont(font);

	std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;
	
	// game loop
	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;

		//print journal on right side of window
		sf::Text journal(players[current_player]->sNotebook(), font, 20);
		journal.setPosition(window.getSize().x - (window.getSize().x / 4), 0.05);

		// roll for movement
		if (!has_rolled) {
			int die_1 = (rand() % 6) + 1;
			int die_2 = (rand() % 6) + 1;
			steps = die_1 + die_2;
			//system("cls");
			//std::cout << "Player " << current_player + 1 << " rolled a " << die_1 << " and a " << die_2 << std::endl;
			//std::cout << "They can move " << steps << " spaces" << std::endl;
			//std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;
			has_rolled = 1;
		}

		// update text box with current player/step counter
		stepCounterString = players[current_player]->getName() +
			"\nSteps: " + std::to_string(steps) +
			"\nLocation: " + tokensVect[current_player]->get_space()->getName();
		stepCounterText.setString(stepCounterString);


		// event handling for move state
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (game_state == 1) {
					//move a piece right
					if (event.key.code == sf::Keyboard::Right)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->getToken()->get_space(), 
								boardArray[players[current_player]->getToken()->get_row()][players[current_player]->getToken()->get_col() + 1], 
								steps)) {

								players[current_player]->getToken()->move_token(width, 0, 0, 1, boardArray);
							}
						}

						break;
					}

					//move a piece left
					if (event.key.code == sf::Keyboard::Left)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->getToken()->get_space(), 
								boardArray[players[current_player]->getToken()->get_row()][players[current_player]->getToken()->get_col() - 1], 
								steps)) {

								players[current_player]->getToken()->move_token(-width, 0, 0, -1, boardArray);
							}
						}

						break;
					}

					//movve a piece down
					if (event.key.code == sf::Keyboard::Down)
					{

						if (steps > 0) {
							if (isValidMove(players[current_player]->getToken()->get_space(), 
								boardArray[players[current_player]->getToken()->get_row() + 1][players[current_player]->getToken()->get_col()], 
								steps)) {

								players[current_player]->getToken()->move_token(0, height, 1, 0, boardArray);
							}
						}
						break;
					}

					//move a piece up
					if (event.key.code == sf::Keyboard::Up)
					{
						if (steps > 0) {
							if (isValidMove(players[current_player]->getToken()->get_space(), 
								boardArray[players[current_player]->getToken()->get_row() - 1][players[current_player]->getToken()->get_col()], 
								steps)) {

								players[current_player]->getToken()->move_token(0, -height, -1, 0, boardArray);
							}
						}
						break;
					}

					// end turn
					if (event.key.code == sf::Keyboard::Enter)
					{
						// if player ends turn in a room, switch to suggestions state
						if (players[current_player]->getToken()->get_space()->isRoom())
						{
							game_state = 0;
						}
						else {


							// change player
							current_player++;
							has_rolled = 0;

							if (current_player > num_players)
							{
								current_player = 0;

							}
						}
						
					}

					break;
				}
			default:
				break;
			}
		}

		// suggestion state
		if (game_state == 0) {

			vector<string> playerSuggest;
			playerSuggest = players[current_player]->makeSuggestion();

			cout << "Player " << current_player + 1 << " has suggested:" << endl;
			cout << playerSuggest[0] << " with the " << playerSuggest[1] << " in the " << playerSuggest[2] << endl;

			int revealingPlayer = current_player + 1;
			if (revealingPlayer > num_players) {
				revealingPlayer = 0;
			}

			while (revealingPlayer != current_player) {
				if (players[revealingPlayer]->containsCard(playerSuggest)) {

					cout << "\n" << players[revealingPlayer]->getName() << "\'s point of view: " << endl;
					string shownCard = players[revealingPlayer]->showCard(playerSuggest);
					cout << "\n==Returning from " << players[revealingPlayer]->getName() << "\'s point of view: " << endl;
					cout << "The card that was shown to the player was: " << shownCard << endl;
					cout << endl;
					break;
				}
				else {
					cout << players[revealingPlayer]->getName() << " didn't have any cards from Player 1's suggestion" << endl;
				}
				revealingPlayer++;
				if (revealingPlayer > num_players) {
					revealingPlayer = 0;
				}
			}
			// go back to move state
			game_state = 1;
			current_player++;
			has_rolled = 0;

			if (current_player > num_players)
			{
				current_player = 0;

			}

		}


		window.clear();

		// draw sprites
		window.draw(rendered_board);
		for (int i = 0; i < tokensVect.size(); i++) {
			window.draw(tokensVect[i]->get_token());
		}
		window.draw(stepCounterText);


		// draw player hands
		for (int i = 0; i < 3; i++) {
			window.draw(players[current_player]->getHand()[i]->getSprite());
		}
		window.draw(journal);
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






