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
#include "game.hpp"
#include "CardButton.hpp"
#include "NotebookButton.hpp"
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

	//// update notebook with cards in hand
	//for (int i = 0; i < players.size(); i++) {
	//	for (int j = 0; j < players[i]->getHand().size(); j++) {
	//		NotebookEntities nCard = players[i]->nCard(players[i]->getHand()[j]->getName());
	//		players[i]->updateNotebook(nCard, 0, 0);
	//	}
	//}

	//control variables for changing player control
	int current_player = 0;
	int num_players = players.size() - 1;

	//player step count for moving
	int steps; // keep track of steps left
	int roll; // keep track of starting roll
	bool has_rolled = 0;

	// game state control variable,  1 = move state, 0 = suggestion state, 2 = accusation state, 3 = game won
	int game_state = 1;
	
	// control variable for suggestion phase. 0 = picking people, 1 = picking weapon, 2 = revealing cards
	int suggestion_phase = 0;
	int accusation_phase = 0;
	bool noReveal = 0;

	//making text box for player/step counter
	sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}
	sf::Text stepCounterText;
	string stepCounterString;
	stepCounterText.setFont(font);

	sf::Text suggestionText;
	suggestionText.setFont(font);

	sf::Text controlsText;
	controlsText.setFont(font);
	controlsText.move(sf::Vector2f(1000, 750));
	controlsText.setString("\t\tControls:\nArrow keys to move\n'A' to make an accusastion\n'Enter' to make suggestion/\n\tend turn\n'P' to use a secret passage");

	sf::Text endText;
	endText.setFont(font);
	endText.setCharacterSize(50);
	endText.move(sf::Vector2f(300, 140));
	

	std::cout << "Move with the arrow keys. Press 'Enter' when you are done moving." << std::endl;

	// create card buttons for suggestions/accusations
	vector<CardButton*> b_people = createButtonArray(0);
	vector<CardButton*> b_weapons = createButtonArray(1);
	vector<CardButton*> b_rooms = createButtonArray(2);
	

	// vector to hold the player's suggestion
	vector<string> playerSuggest;
	vector<string> choices;
	vector<CardButton> choiceButtons;
	CardButton* revealedCard = 0;
	string revealingPlayerName = "";


	// vector holding player's accusation
	vector<string> playerAccusation;

	NotebookButton testButton(0, sf::Vector2f(1100, 10 +18));

	vector<NotebookButton*> b_notebook = createNotebookButtons();

	window.setFramerateLimit(60);
	
	// game loop
	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;
		sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		//print journal on right side of window
		sf::Font journalFont;

		sf::Text journal(players[current_player]->sNotebook(), font, 20);
		journal.setPosition(window.getSize().x - (window.getSize().x / 4), 0.05);

		// roll for movement
		if (!has_rolled) {
			int die_1 = (rand() % 6) + 1;
			int die_2 = (rand() % 6) + 1;
			roll = die_1 + die_2; // keep track of starting roll
			steps = roll; // keep track of steps left
			has_rolled = 1;
		}

		// update text box with current player/step counter
		stepCounterString = players[current_player]->getName() +
			"\nSteps: " + std::to_string(steps) +
			"\nLocation: " + tokensVect[current_player]->get_space()->getName();
		stepCounterText.setString(stepCounterString);


		// event handling for move state
		if (game_state == 1) {
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
								if (isValidMove(players[current_player],
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
								if (isValidMove(players[current_player],
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
								if (isValidMove(players[current_player],
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
								if (isValidMove(players[current_player],
									boardArray[players[current_player]->getToken()->get_row() - 1][players[current_player]->getToken()->get_col()],
									steps)) {
									players[current_player]->getToken()->move_token(0, -height, -1, 0, boardArray);
									
								}
							}
							break;
						}
						// use secret passage, begining of turn only
						if (event.key.code == sf::Keyboard::P) {
							// can only use passage at begining of turn i.e no steps moved
							if (roll == steps) {
								int passageUsed = 0;
								passageUsed = secretPassage(players[current_player]->getToken(), boardArray);
								if (passageUsed) {
									// turn steps to 0, and allow player to make a suggestion
									steps = 0;
									players[current_player]->setSuggested(0);
								}
							}
						}
						// end turn
						if (event.key.code == sf::Keyboard::Enter)
						{
							// if player ends turn in a room, switch to suggestions state, unless they started in the room and have not moved out
							if (players[current_player]->getToken()->get_space()->isRoom() && players[current_player]->getSuggested() == 0)
							{
								game_state = 0;
								players[current_player]->setSuggested(1);
							}
							else {
								// change player
								int count = 0;
								has_rolled = 0;
							
								do {
									current_player++;
									if (current_player > num_players)
									{
										current_player = 0;
									}

									count++;
									// check if all players are dead
									if (count > num_players + 1) {
										game_state = 4;
										break;
									}
								} while (players[current_player]->getAlive() != 1);

							}
						}
						// make accusation
						if (event.key.code == sf::Keyboard::A) {
							game_state = 2; // accusation state
						
						}
						break;

						
					}
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) {
						for (int i = 0; i < b_notebook.size(); i++) {
							if (b_notebook[i]->update(mouse)) {
								players[current_player]->flipNotebook(i);
								
							}
						}
					}

				default:
					break;
				}
			}
		}
		// suggestion state
		else if (game_state == 0) {
			// variable used to let user see their suggestion choices
			int next_phase = 0;
			std::string suggestionChoice;

			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Enter) {
						next_phase = 1;
					}
				default:
					break;
				}

				if (suggestion_phase == 0) { // player suggests a suspect
					suggestionText.setString("Suggestion: Choose a Suspect");
					for (int i = 0; i < b_people.size(); i++) {
						b_people[i]->update(mouse);
						if (b_people[i]->isPressed()) {
							suggestionChoice = b_people[i]->getName();
							suggestion_phase++;
							playerSuggest.push_back(suggestionChoice);
						}
					}
				}
				else if (suggestion_phase == 1) { // player suggests a weapon
					suggestionText.setString("Suggestion: Choose a Weapon");
					for (int i = 0; i < b_weapons.size(); i++) {
						b_weapons[i]->update(mouse);
						if (b_weapons[i]->isPressed()) {
							suggestionChoice = b_weapons[i]->getName();
							suggestion_phase++;
							playerSuggest.push_back(suggestionChoice);
						}
					}
				}
				else if (suggestion_phase == 2) { // current location is automatically suggested
					suggestionChoice = players[current_player]->getToken()->get_space()->getName();
					playerSuggest.push_back(suggestionChoice);
					
					suggestion_phase++;
				}
				else if (suggestion_phase == 3) { // show which cards were suggested
					suggestionText.setString("You have Suggested:\nPress 'Enter' to continue . . .");
					if (next_phase == 1) {
						suggestion_phase++;
						next_phase = 0;
					}
				}
				else if (suggestion_phase == 4) { // revealing player picks a card

					if (next_phase == 1 && noReveal == 1) { // if no card is revealed, then press enter to continue
						suggestion_phase = suggestion_phase + 2; // skip the phase revealing a card
						next_phase = 0;
					}
				}		
				// go back to move state
				else if (suggestion_phase == 5) { // show the current player what card was revealed
					
					if (next_phase == 1) {
						suggestion_phase++;
						next_phase = 0;
					}
				}
				else if (suggestion_phase == 6) {
					game_state = 1;
					// go back to moving phase, current turn stays the same to allow player to make an accustion
				

					// reset player suggestion variables
					playerSuggest.clear();
					suggestion_phase = 0;

				
				}
			}
		}
		else if (game_state == 2) { // accusation state
			int endPhase = 0;
			int nextPhase = 0;

			std::string accusationChoice;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Enter) {
						nextPhase = 1;
					}
				default:
					break;
				}

				if (accusation_phase == 0) { // player chooses a suspect
					suggestionText.setString("Accusation: Choose a Suspect");
					for (int i = 0; i < b_people.size(); i++) {
						b_people[i]->update(mouse);
						if (b_people[i]->isPressed()) {
							accusationChoice = b_people[i]->getName();
							accusation_phase++;
							playerAccusation.push_back(accusationChoice);
						}
					}
				}
				else if (accusation_phase == 1) { // player chooses a weapon
					suggestionText.setString("Accusation: Choose a Weapon");
					for (int i = 0; i < b_weapons.size(); i++) {
						b_weapons[i]->update(mouse);
						if (b_weapons[i]->isPressed()) {
							accusationChoice = b_weapons[i]->getName();
							accusation_phase++;
							playerAccusation.push_back(accusationChoice);
						}
					}
				}
				else if (accusation_phase == 2) { // player chooses a room
					suggestionText.setString("Accusation: Choose a Location");
					for (int i = 0; i < b_rooms.size(); i++) {
						b_rooms[i]->update(mouse);
						if (b_rooms[i]->isPressed()) {
							accusationChoice = b_rooms[i]->getName();
							accusation_phase++;
							playerAccusation.push_back(accusationChoice);
						}
					}
				}
				else if (accusation_phase == 3) { // show which cards were suggested
					suggestionText.setString("You have chosen:\nPress 'Enter' to continue . . .");
					if (nextPhase == 1) {
						bool solved = true;
						nextPhase = 0;

						// check solution
						for (int i = 0; i < 3; i++) {
							if (solution[i]->getName() != playerAccusation[i]) {
								solved = false;
								break;
							}
						}
						// incorrect solution, go to next player
						if (solved == false) {
							accusation_phase++;
							players[current_player]->getToken()->setBlack(); // turn the player's token to black
							players[current_player]->setAlive(0);
						}
						// case solved, end game
						else if (solved == true) {
							game_state = 3;
						}

					}
				}
				else if (accusation_phase == 4) { // tell the player has the incorrect solution
					if (nextPhase == 1) {
						nextPhase = 0;
						endPhase = 1;
					}
				}
				
				// if the game hasn't ended, go to the next player
				if (endPhase == 1) {
					game_state = 1;
					int count = 0;
					do {
						
						current_player++;
						if (current_player > num_players)
						{
							current_player = 0;
						}

						count++;
						if (count > num_players + 1) {
							game_state = 4;
							break;
						}
					} while (players[current_player]->getAlive() != 1);
					has_rolled = 0;
					accusation_phase = 0;
					playerAccusation.clear();
					
				}
			}
		}
		// win screen
		else if (game_state == 3) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
				}
			}
		}
		// everybody loses
		else if (game_state == 4) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
				}
			}
		}

		window.clear();

		// draw sprites
		if (game_state == 1) { // moving phase
			window.draw(rendered_board);
			for (int i = 0; i < tokensVect.size(); i++) {
				window.draw(tokensVect[i]->get_token());
			}
			window.draw(stepCounterText);
			window.draw(controlsText);
			// draw player hands
			for (int i = 0; i < 3; i++) {
				window.draw(players[current_player]->getHand()[i]->getSprite());
			}


			window.draw(journal);
			for (int i = 0; i < b_notebook.size(); i++) {
				b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
			}
		}
		else if (game_state == 0) { // suggestion phase


					////updating all player notebooks
					//for (int i = 0; i < players.size(); i++) {				
					//	NotebookEntities nCard = players[i]->nCard(shownCard);
					//	players[i]->updateNotebook(nCard, 0, 0);						
					//}


			if (suggestion_phase == 0) { // render buttons for people
				for (int i = 0; i < b_people.size(); i++) {
					b_people[i]->render(&window);
					b_people[i]->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				}
				// render notebook
				window.draw(journal);
				for (int i = 0; i < b_notebook.size(); i++) {
					b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
				}
			}
			else if (suggestion_phase == 1) { // render buttons for weapons
				for (int i = 0; i < b_weapons.size(); i++) {
					b_weapons[i]->render(&window);
					b_weapons[i]->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				}
				// render notebook
				window.draw(journal);
				for (int i = 0; i < b_notebook.size(); i++) {
					b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
				}
			}
			// suggestion phase 2 does not draw anything
			else if (suggestion_phase == 3) {  // show which cards were suggested
				for (int i = 0; i < b_people.size(); i++) {
					if (b_people[i]->getName() == playerSuggest[0]) {
						b_people[i]->setButtonPos(sf::Vector2f(375, 140));
						b_people[i]->update(mouse);
						b_people[i]->render(&window);
						b_people[i]->resetPos();
					}
				}
				for (int i = 0; i < b_weapons.size(); i++) {
					if (b_weapons[i]->getName() == playerSuggest[1]) {
						b_weapons[i]->setButtonPos(sf::Vector2f(575, 140));
						b_weapons[i]->update(mouse);
						b_weapons[i]->render(&window);
						b_weapons[i]->resetPos();
					}
				}
				for (int i = 0; i < b_rooms.size(); i++) {
					if (b_rooms[i]->getName() == playerSuggest[2]) {
						b_rooms[i]->setButtonPos(sf::Vector2f(775, 140));
						b_rooms[i]->update(mouse);
						b_rooms[i]->render(&window);
						b_rooms[i]->resetPos();
					}
				}
			}
			// player chooses which card to show
			else if (suggestion_phase == 4) { // phase for revealing player

				noReveal = 0; // reset control flag signally if there is a card to reveal;
				int revealingPlayer = current_player + 1;


				if (revealingPlayer > num_players) {
					revealingPlayer = 0;
				}

				while (revealingPlayer != current_player) { // find the first player to have a matching card
					if (players[revealingPlayer]->containsCard(playerSuggest)) {
						suggestionText.setString(players[revealingPlayer]->getName() + " choose a card to reveal");
						revealingPlayerName = players[revealingPlayer]->getName();
						for (int i = 0; i < playerSuggest.size(); i++) {
							for (int j = 0; j < players[revealingPlayer]->getHand().size(); j++) {

								if (players[revealingPlayer]->getHand()[j]->getName() == playerSuggest[i]) {
									choices.push_back(playerSuggest[i]);						
								}
							}
						}
						break;
					}
					revealingPlayer++;
					if (revealingPlayer > num_players) {
						revealingPlayer = 0;
					}									
				}
				if (revealingPlayer != current_player) { // render buttons for revealing player
					for (int i = 0; i < choices.size(); i++) {
						for (int j = 0; j < b_people.size(); j++) {
							if (b_people[j]->getName() == choices[i]) {
								b_people[j]->setButtonPos(sf::Vector2f(375, 140));
								b_people[j]->update(mouse);
								if (b_people[j]->isPressed()) {
									suggestion_phase++;
									revealedCard = b_people[j];
								}
								b_people[j]->render(&window);
								b_people[j]->resetPos();
							}
						}
						for (int k = 0; k < b_weapons.size(); k++) {
							if (b_weapons[k]->getName() == choices[i]) {
								b_weapons[k]->setButtonPos(sf::Vector2f(575, 140));
								b_weapons[k]->update(mouse);
								if (b_weapons[k]->isPressed()) {
									suggestion_phase++;
									revealedCard = b_weapons[k];
								}
								b_weapons[k]->render(&window);
								b_weapons[k]->resetPos();
							}
						}
						for (int h = 0; h < b_rooms.size(); h++) {
							if (b_rooms[h]->getName() == choices[i]) {
								b_rooms[h]->setButtonPos(sf::Vector2f(775, 140));
								b_rooms[h]->update(mouse);
								if (b_rooms[h]->isPressed()) {
									suggestion_phase++;
									revealedCard = b_rooms[h];
								}
								b_rooms[h]->render(&window);
								b_rooms[h]->resetPos();
							}
						}
						window.draw(journal);
						for (int i = 0; i < b_notebook.size(); i++) {
							b_notebook[i]->render(&window, players[revealingPlayer]->getNewNotebook()[i]);
						}
					}
				}
				else { // no matching card was found
					suggestionText.setString("No one had anything to show\n Press Enter to continue . . .");
					noReveal = 1;
				}			

				choices.clear();
			}
			else if (suggestion_phase == 5) { // show the revealed card
				suggestionText.setString(revealingPlayerName + " reveals:\n Press Enter to coninue . . . ");
				revealedCard->setButtonPos(sf::Vector2f(575, 340));
				revealedCard->update(mouse);
				revealedCard->render(&window);
				revealedCard->resetPos();
			}
			window.draw(suggestionText);
		}


		
		

		else if (game_state == 2) { // accusation phase
			if (accusation_phase == 0) { // render buttons for people
				for (int i = 0; i < b_people.size(); i++) {
					b_people[i]->render(&window);
					b_people[i]->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				}
				window.draw(journal);
				for (int i = 0; i < b_notebook.size(); i++) {
					b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
				}
			}
			else if (accusation_phase == 1) { // render buttons for weapons
					for (int i = 0; i < b_weapons.size(); i++) {
					b_weapons[i]->render(&window);
					b_weapons[i]->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				}
					window.draw(journal);
					for (int i = 0; i < b_notebook.size(); i++) {
						b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
					}
			}
			else if (accusation_phase == 2) { // render buttons for rooms
				for (int i = 0; i < b_rooms.size(); i++) {
					b_rooms[i]->render(&window);
					b_rooms[i]->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				}
				window.draw(journal);
				for (int i = 0; i < b_notebook.size(); i++) {
					b_notebook[i]->render(&window, players[current_player]->getNewNotebook()[i]);
				}
			}
			else if (accusation_phase == 3) { // show which cards were chosen for accusation
				for (int i = 0; i < b_people.size(); i++) {
					if (b_people[i]->getName() == playerAccusation[0]) {
						b_people[i]->setButtonPos(sf::Vector2f(375, 140));
						b_people[i]->update(mouse);
						b_people[i]->render(&window);
						b_people[i]->resetPos();
					}
				}
				for (int i = 0; i < b_weapons.size(); i++) {
					if (b_weapons[i]->getName() == playerAccusation[1]) {
						b_weapons[i]->setButtonPos(sf::Vector2f(575, 140));
						b_weapons[i]->update(mouse);
						b_weapons[i]->render(&window);
						b_weapons[i]->resetPos();
					}
				}
				for (int i = 0; i < b_rooms.size(); i++) {
					if (b_rooms[i]->getName() == playerAccusation[2]) {
						b_rooms[i]->setButtonPos(sf::Vector2f(775, 140));
						b_rooms[i]->update(mouse);
						b_rooms[i]->render(&window);
						b_rooms[i]->resetPos();
					}
				}
			}
			else if (accusation_phase == 4) { // incorrect accusation
				suggestionText.setString(players[current_player]->getName() + " is incorrect!\n press Enter to continue");
				for (int i = 0; i < b_people.size(); i++) {
					if (b_people[i]->getName() == playerAccusation[0]) {
						b_people[i]->setButtonPos(sf::Vector2f(375, 340));
						b_people[i]->update(mouse);
						b_people[i]->render(&window);
						b_people[i]->resetPos();
					}
				}
				for (int i = 0; i < b_weapons.size(); i++) {
					if (b_weapons[i]->getName() == playerAccusation[1]) {
						b_weapons[i]->setButtonPos(sf::Vector2f(575, 340));
						b_weapons[i]->update(mouse);
						b_weapons[i]->render(&window);
						b_weapons[i]->resetPos();
					}
				}
				for (int i = 0; i < b_rooms.size(); i++) {
					if (b_rooms[i]->getName() == playerAccusation[2]) {
						b_rooms[i]->setButtonPos(sf::Vector2f(775, 340));
						b_rooms[i]->update(mouse);
						b_rooms[i]->render(&window);
						b_rooms[i]->resetPos();
					}
				}
			}
			window.draw(suggestionText);
		}
		else if (game_state == 3) { // game won
		
		
			for (int i = 0; i < b_people.size(); i++) {
				if (b_people[i]->getName() == playerAccusation[0]) {
					b_people[i]->setButtonPos(sf::Vector2f(375, 340));
					b_people[i]->update(mouse);
					b_people[i]->render(&window);
					b_people[i]->resetPos();
				}
			}
			for (int i = 0; i < b_weapons.size(); i++) {
				if (b_weapons[i]->getName() == playerAccusation[1]) {
					b_weapons[i]->setButtonPos(sf::Vector2f(575, 340));
					b_weapons[i]->update(mouse);
					b_weapons[i]->render(&window);
					b_weapons[i]->resetPos();
				}
			}
			for (int i = 0; i < b_rooms.size(); i++) {
				if (b_rooms[i]->getName() == playerAccusation[2]) {
					b_rooms[i]->setButtonPos(sf::Vector2f(775, 340));
					b_rooms[i]->update(mouse);
					b_rooms[i]->render(&window);
					b_rooms[i]->resetPos();
				}

				endText.setString(players[current_player]->getName() + " has solved the case!");
				window.draw(endText);
			}
			
		}
		else if (game_state == 4) { // everyone loses

			for (int i = 0; i < b_people.size(); i++) {
				if (b_people[i]->getName() == solution[0]->getName()) {
					b_people[i]->setButtonPos(sf::Vector2f(375, 340));
					b_people[i]->update(mouse);
					b_people[i]->render(&window);
					b_people[i]->resetPos();
				}
			}
			for (int i = 0; i < b_weapons.size(); i++) {
				if (b_weapons[i]->getName() == solution[1]->getName()) {
					b_weapons[i]->setButtonPos(sf::Vector2f(575, 340));
					b_weapons[i]->update(mouse);
					b_weapons[i]->render(&window);
					b_weapons[i]->resetPos();
				}
			}
			for (int i = 0; i < b_rooms.size(); i++) {
				if (b_rooms[i]->getName() == solution[2]->getName()) {
					b_rooms[i]->setButtonPos(sf::Vector2f(775, 340));
					b_rooms[i]->update(mouse);
					b_rooms[i]->render(&window);
					b_rooms[i]->resetPos();
				}
			}
				endText.setString("The case went unsolved!");
				endText.setPosition(sf::Vector2f(500, 140));
				window.draw(endText);
		}

		
		
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

	for (int i = 0; i < b_people.size(); i++) {
		delete b_people[i];
	}

	for (int i = 0; i < b_weapons.size(); i++) {
		delete b_weapons[i];
	}

	for (int i = 0; i < b_rooms.size(); i++) {
		delete b_rooms[i];
	}

	for (int i = 0; i < b_notebook.size(); i++) {
		delete b_notebook[i];
	}
	return 0;
}






