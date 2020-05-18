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
// "token.hpp"
#include "deck.hpp"
#include "game.hpp"
#include <iomanip>



using namespace std;
using std::tuple;

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


	// create the player tokens
	vector<token*> tokensVect = playerTokens(width, height, boardArray);
	// [Scarlet, Mustard, Green, Plum, Peacock, White]


	/////////////////////////////////////creating devin players/////////////////////////////////////////////
	vector<Card*> hand1;
	vector<Card*> hand2;
	vector<Card*> hand3;
	vector<Card*> hand4;
	vector<Card*> hand5;
	vector<Card*> hand6;

	tuple<int, int> pos1;
	tuple<int, int> pos2;
	tuple<int, int> pos3;
	tuple<int, int> pos4;
	tuple<int, int> pos5;
	tuple<int, int> pos6;


	Player* player1 = new Player("Player 1 (Miss Scarlet)", tokensVect[0], hand1, pos1);
	Player* player2 = new Player("Player 2 (Colonel Mustard)", tokensVect[1], hand2, pos2);
	Player* player3 = new Player("Player 3 (Mr. Green)", tokensVect[2], hand3, pos3);
	Player* player4 = new Player("Player 4 (Professor Plum)", tokensVect[3], hand4, pos4);
	Player* player5 = new Player("Player 5 (Mrs. Peacock)", tokensVect[4], hand5, pos5);
	Player* player6 = new Player("Player 6 (Mrs. White)", tokensVect[5], hand6, pos6);

	vector<Player*> players = {player1, player2, player3, player4, player5, player6};

	Deck newDeck;

	vector<Card*> solution = newDeck.getSolution();
	cout << "Suspect: " << solution[0]->getName() << endl;
	cout << "Weapon: " << solution[1]->getName() << endl;
	cout << "Room: " << solution[2]->getName() << endl;

	newDeck.shuffle();

	newDeck.deal(players);
	vector<Card*> player1hand = players[0]->getHand();
	vector<Card*> player2hand = players[1]->getHand();
	vector<Card*> player3hand = players[2]->getHand();
	vector<Card*> player4hand = players[3]->getHand();
	vector<Card*> player5hand = players[4]->getHand();
	vector<Card*> player6hand = players[5]->getHand();

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

	// game state  1 = move state, 0 = suggestion state
	bool game_state = 1;
	

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
			//system("cls");
			std::cout << "Player " << current_player + 1 << " rolled a " << die_1 << " and a " << die_2 << std::endl;
			std::cout << "They can move " << steps << " spaces" << std::endl;
			std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;
			has_rolled = 1;
		}

		stepCounterString = "Player " + std::to_string(current_player + 1) +
			"\nSteps: " + std::to_string(steps) +
			"\nLocation: " + tokensVect[current_player]->get_space()->getName();
		stepCounterText.setString(stepCounterString);
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
							if (isValidMove(tokensVect[current_player]->get_space(), boardArray[tokensVect[current_player]->get_row()][tokensVect[current_player]->get_col() + 1], steps)) {

								tokensVect[current_player]->move_token(width, 0, 0, 1, boardArray);
							}
						}

						break;
					}

					//move a piece left
					if (event.key.code == sf::Keyboard::Left)
					{
						if (steps > 0) {
							if (isValidMove(tokensVect[current_player]->get_space(), boardArray[tokensVect[current_player]->get_row()][tokensVect[current_player]->get_col() - 1], steps)) {

								tokensVect[current_player]->move_token(-width, 0, 0, -1, boardArray);
							}
						}

						break;
					}

					//movve a piece down
					if (event.key.code == sf::Keyboard::Down)
					{

						if (steps > 0) {
							if (isValidMove(tokensVect[current_player]->get_space(), boardArray[tokensVect[current_player]->get_row() + 1][tokensVect[current_player]->get_col()], steps)) {

								tokensVect[current_player]->move_token(0, height, 1, 0, boardArray);
							}
						}
						break;
					}

					//move a piece up
					if (event.key.code == sf::Keyboard::Up)
					{
						if (steps > 0) {
							if (isValidMove(tokensVect[current_player]->get_space(), boardArray[tokensVect[current_player]->get_row() - 1][tokensVect[current_player]->get_col()], steps)) {

								tokensVect[current_player]->move_token(0, -height, -1, 0, boardArray);
							}
						}
						break;
					}

					//change player control
					if (event.key.code == sf::Keyboard::Enter)
					{
						// if player ends turn in a room
						if (tokensVect[current_player]->get_space()->isRoom())
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


		window.clear();

		// draw sprites
		window.draw(rendered_board);
		for (int i = 0; i < tokensVect.size(); i++) {
			window.draw(tokensVect[i]->get_token());
		}
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
//#include <iostream>
//#include "Player.hpp"
//#include "Token.hpp"
//#include "Deck.hpp"
//#include "Game.hpp"
//#include <iomanip>
//using std::cout;
//using std::endl;
//using std::tuple;
//
////#include "gameInit.hpp"
//
//
//int main() {
//	
//
//	////Generating test values
//	//std::vector<Card*> testHand;
//	//Card* c1 = new Card("Suspect_1", SUSPECT);
//	//testHand.push_back(c1);
//	//Card* c2 = new Card("Suspect_2", SUSPECT);
//	//testHand.push_back(c2);
//	//Card* c3 = new Card("Weapon_1", WEAPON);
//	//testHand.push_back(c3);
//	//Card* c4 = new Card("Weapon_2", WEAPON);
//	//testHand.push_back(c4);
//	//Card* c5 = new Card("Place_1", ROOM);
//	//testHand.push_back(c5);
//	//Card* c6 = new Card("Place_2", ROOM);
//	//testHand.push_back(c6);
//	//std::tuple<int, int> currentPos = std::make_tuple(1, 1);
//
//	////Using the overloaded Token constructor
//	//Token* t1 = new Token("Knife", WEAPON_T, currentPos);
//	//std::cout << t1->getName() << std::endl;
//
//	////Using the overloaded Player constructor
//	//Player* p1 = new Player("Devin Mourrain", MUSTARD, testHand, currentPos);
//	//
//	////Position usage example
//	//std::cout << "Initial position: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;
//	//p1->updatePosition(std::make_tuple(1, 4));
//	//std::cout << "After moving: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;
//
//
//	////Accessing cards within a player's hand
//	//std::cout << "P1's Cards before removing a card: " << std::endl;
//	//for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
//	//	std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
//	//}
//
//	////Removing cards example
//	//std::cout << "P1's Cards after removing a card: " << std::endl;
//	//p1->removeCard("Suspect_2");
//	//for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
//	//	std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
//	//}
//
//	////Notebook usage example
//	//p1->printNotebook();
//	//p1->updateNotebook(MUSTARD_N, 0, 1);
//	//std::cout << "===" << std::endl;
//	//p1->printNotebook();
//	//std::cout << "===" << std::endl;
//	//p1->updateNotebook(KITCHEN_N, 0, 1);
//	//p1->updateNotebook(BILLIARD_N, 0, 0);
//	//p1->printNotebook();
//	//std::cout << "===" << std::endl;
//
//	//cardSetup();
//	
//	// For testing
//	vector<Card*> hand1;
//	//hand1.push_back(new Card("Colonel Mustard", SUSPECT));
//	//hand1.push_back(new Card("Wrench", WEAPON));
//	//hand1.push_back(new Card("Lounge", ROOM));
//	vector<Card*> hand2;
//	//hand2.push_back(new Card("Mr. Green", SUSPECT));
//	//hand2.push_back(new Card("Knife", WEAPON));
//	//hand2.push_back(new Card("Hall", ROOM));
//	vector<Card*> hand3;
//	//hand3.push_back(new Card("Mrs. Peacock", SUSPECT));
//	//hand3.push_back(new Card("Lead Pipe", WEAPON));
//	//hand3.push_back(new Card("Ballroom", ROOM));
//	vector<Card*> hand4;
//	//hand4.push_back(new Card("Professor Plum", SUSPECT));
//	//hand4.push_back(new Card("Revolver", WEAPON));
//	//hand4.push_back(new Card("Study", ROOM));
//	vector<Card*> hand5;
//	//hand5.push_back(new Card("Miss Scarlet", SUSPECT));
//	//hand5.push_back(new Card("Candlestick", WEAPON));
//	//hand5.push_back(new Card("Library", ROOM));
//	vector<Card*> hand6;
//	//hand6.push_back(new Card("Mrs. White", SUSPECT));
//	//hand6.push_back(new Card("Rope", WEAPON));
//	//hand6.push_back(new Card("Billiard Room", ROOM));
//
//	tuple<int, int> pos1;
//	tuple<int, int> pos2;
//	tuple<int, int> pos3;
//	tuple<int, int> pos4;
//	tuple<int, int> pos5;
//	tuple<int, int> pos6;
//
//	Player* player1 = new Player("Player 1", MUSTARD, hand1, pos1);
//	Player* player2 = new Player("Player 2", SCARLET, hand2, pos2);
//	Player* player3 = new Player("Player 3", PEACOCK, hand3, pos3);
//	Player* player4 = new Player("Player 4", GREEN, hand4, pos4);
//	Player* player5 = new Player("Player 5", WHITE, hand5, pos5);
//	Player* player6 = new Player("Player 6", PLUM, hand6, pos6);
//	vector<Player*> players = {player1, player2, player3, player4, player5, player6};
//
//	Deck newDeck;
//
//	vector<Card*> solution = newDeck.getSolution();
//	cout << "Suspect: " << solution[0]->getName() << endl;
//	cout << "Weapon: " << solution[1]->getName() << endl;
//	cout << "Room: " << solution[2]->getName() << endl;
//
//	newDeck.shuffle();
//
//	newDeck.deal(players);
//	vector<Card*> player1hand = players[0]->getHand();
//	vector<Card*> player2hand = players[1]->getHand();
//	vector<Card*> player3hand = players[2]->getHand();
//	vector<Card*> player4hand = players[3]->getHand();
//	vector<Card*> player5hand = players[4]->getHand();
//	vector<Card*> player6hand = players[5]->getHand();
//
//	std::cout << "Player hands:\n===" << std::endl;
//	for (int i = 0; i < player1hand.size(); i++)
//	{
//		cout << players[0]->getName() << " has " << player1hand[i]->getName() << endl;
//	}
//	cout << endl;
//		
//	for (int i = 0; i < player2hand.size(); i++)
//	{
//		cout << players[1]->getName() << " has " << player2hand[i]->getName() << endl;
//	}
//	cout << endl;
//
//	for (int i = 0; i < player3hand.size(); i++)
//	{
//		cout << players[2]->getName() << " has " << player3hand[i]->getName() << endl;
//	}
//	cout << endl;
//
//	for (int i = 0; i < player4hand.size(); i++)
//	{
//		cout << players[3]->getName() << " has " << player4hand[i]->getName() << endl;
//	}
//	cout << endl;
//
//	for (int i = 0; i < player5hand.size(); i++)
//	{
//		cout << players[4]->getName() << " has " << player5hand[i]->getName() << endl;
//	}
//	cout << endl;
//
//	for (int i = 0; i < player6hand.size(); i++)
//	{
//		cout << players[5]->getName() << " has " << player6hand[i]->getName() << endl;
//	}
//	cout << endl;
//	
//	// Suggestion test
//	vector<string> player1suggest;
//	player1suggest = players[0]->makeSuggestion();
//	
//	cout << "Player 1 has suggested:" << endl;
//	cout << player1suggest[0] << " with the " << player1suggest[1] << " in the " << player1suggest[2] << endl;
//	
//	for (int i = 1; i < players.size(); i++) {			//currently hardcoded to start at 1 to ignore Player 1's hand, but we may want to return which player made the suggestion in the vector so we can skip them
//		if (players[i]->containsCard(player1suggest)) {
//			//cout << players[i].getName() << " had at least one of the cards from Player 1's suggestion" << endl;
//			//the point of view stuff below is somewhat trivial as all of this is global right now, but
//			//minimally we have the ability to prompt a user to show a card after verifying that they have at least one card from the suggestion
//			cout << "\n" << players[i]->getName() << "\'s point of view: " << endl;
//			string shownCard = players[i]->showCard(player1suggest);
//			cout << "\n==Returning from " << players[i]->getName() << "\'s point of view: " << endl;
//			cout << "The card that was shown to the player was: " << shownCard << endl;
//			cout << endl;
//		}
//		else {
//			//cout << players[i].getName() << " didn't have any cards from Player 1's suggestion" << endl;
//		}
//	}
//
//	/* Game class test---not really working rn
//	vector<string> player1suggest = { "Mrs. White", "Revolver", "Lounge" };
//	Game newGame = Game();
//	newGame.checkSuggestion(MUSTARD, player1suggest);*/
//
//	for (int i = 0; i < players.size(); i++) {
//		delete players[i];
//	}
//
//	return 0;
//}





