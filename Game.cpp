/**************************************************************************************************
 * Program name: Game.cpp
 * Author: Abigail Minchella
 * Date: 5/8/2020
 * Description: A class that creates an instance of the Clue game (put any odd logic functions
 * that might require a full game setup in here)
**************************************************************************************************/
#include "Game.hpp"
#include <iostream>
#include <tuple>
using std::cout;
using std::cin;
using std::endl;
using std::tuple;

/**************************************************************************************************
                                            Game::Game()
 * Description: The constructor for the Game class. Sets up the game.
**************************************************************************************************/
Game::Game()
{
	//// Initialize players
	//vector<Card*> hand1;
	//vector<Card*> hand2;
	//vector<Card*> hand3;
	//vector<Card*> hand4;
	//vector<Card*> hand5;
	//vector<Card*> hand6;

	//tuple<int, int> pos1;
	//tuple<int, int> pos2;
	//tuple<int, int> pos3;
	//tuple<int, int> pos4;
	//tuple<int, int> pos5;
	//tuple<int, int> pos6;

	//Player* player1 = new Player("Player 1", MUSTARD, hand1, pos1);
	//Player* player2 = new Player("Player 2", SCARLET, hand2, pos2);
	//Player* player3 = new Player("Player 3", PEACOCK, hand3, pos3);
	//Player* player4 = new Player("Player 4", GREEN, hand4, pos4);
	//Player* player5 = new Player("Player 5", WHITE, hand5, pos5);
	//Player* player6 = new Player("Player 6", PLUM, hand6, pos6);
	//players = { player1, player2, player3, player4, player5, player6 };

	//// Initialize deck
	//gameDeck = Deck();
	//solution = gameDeck.getSolution();
	//gameDeck.shuffle();
	//gameDeck.deal(players);
}

/*************************************************************************************************
					void Game::checkSuggestion(PlayerToken player, vector<string> suggestion)
 * Description: Takes a suggestion that a player made and checks it against the other players' 
 * hands. Prompts a player who has a matching card to show what they have to the other player.
*************************************************************************************************/
void Game::checkSuggestion(token* player, vector<string> suggestion)
{
	// Figure out which player is the one who made the suggestion
	int playerPos;
	for (int i = 0; i < 6; i++)
	{
		token* thisPlayer = players[i]->getToken();
		if (thisPlayer == player)
		{
			playerPos = i;
		}
	}

	// Check other players' hands
	bool done = false;
	int nextPlayer = playerPos + 1;
	while (!done)
	{
		// Check the index of the next player (if it goes up to 6, loop back down to 0
		if (nextPlayer == 6)
		{
			nextPlayer = 0;
		}
		
		// Get that player's hand and compare to the suggestion items
		vector<Card*> nextHand = players[nextPlayer]->getHand();
		for (int i = 0; i < nextHand.size(); i++)
		{
			string cardName = nextHand[i]->getName();
			// If the current card is the same as any of the suggestion items, change loop condition
			if (cardName == suggestion[0] || cardName == suggestion[1] || cardName == suggestion[2])
			{
				done = true;
			}
		}
		
		// Check to see if the loop is going to break, if not, increment player
		if (done != true)
		{
			nextPlayer++;
			// If the next player is the original player, end loop
			if (nextPlayer == playerPos)
			{
				done = true;
			}
		}
	}

	// If there were no matches found, output message
	if (playerPos == nextPlayer)
	{
		cout << "No matches were found in any player hands" << endl;
	}
	// Otherwise, get the hand and push the possible cards to a vector
	else
	{
		vector<Card*> proofHand = players[nextPlayer]->getHand();
		vector<Card*> possibleCards;
		for (int i = 0; i < proofHand.size(); i++)
		{
			string cardName = proofHand[i]->getName();
			if (cardName == suggestion[0] || cardName == suggestion[1] || cardName == suggestion[2])
			{
				possibleCards.push_back(proofHand[i]);
			}
		}

		// Replace with nice client-server code that only prompts one player and doesn't print to the console
		// Prompt player to choose a card to show
		cout << players[nextPlayer]->getName() << ", you have cards that match the suggestion. "
			<< "Which card would you like to show " << players[playerPos]->getName() << "?"
			<< "(Enter the number of the card)" << endl;
		// Output the matching cards
		for (int i = 0; i < possibleCards.size(); i++)
		{
			cout << i << ": " << possibleCards[i]->getName() << endl;
		}

		int choice;
		cin >> choice;
		
		// Validate input
		bool valid = false;
		while (!valid)
		{
			if (choice > 0 || choice < possibleCards.size())
			{
				valid = true;
			}
			else
			{
				cout << "Invalid input. Please enter a number 0 to " << possibleCards.size();
				cin >> choice;
			}
		}

		// Replace with some sort of nice client-server code that only shows the player making the suggestion
		cout << players[playerPos]->getName() << ", " << players[nextPlayer]->getName()
			<< " has chosen to show you that they have " << possibleCards[choice]->getName()
			<< " in their hand" << endl;
	}
}
