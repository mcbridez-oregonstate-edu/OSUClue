#include <iostream>
#include "Player.hpp"
#include "Token.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include <iomanip>
using std::cout;
using std::endl;
using std::tuple;

//#include "gameInit.hpp"


int main() {
	

	//Generating test values
	std::vector<Card*> testHand;
	Card* c1 = new Card("Suspect_1", SUSPECT);
	testHand.push_back(c1);
	Card* c2 = new Card("Suspect_2", SUSPECT);
	testHand.push_back(c2);
	Card* c3 = new Card("Weapon_1", WEAPON);
	testHand.push_back(c3);
	Card* c4 = new Card("Weapon_2", WEAPON);
	testHand.push_back(c4);
	Card* c5 = new Card("Place_1", ROOM);
	testHand.push_back(c5);
	Card* c6 = new Card("Place_2", ROOM);
	testHand.push_back(c6);
	std::tuple<int, int> currentPos = std::make_tuple(1, 1);

	//Using the overloaded Token constructor
	Token* t1 = new Token("Knife", WEAPON_T, currentPos);
	std::cout << t1->getName() << std::endl;

	//Using the overloaded Player constructor
	Player* p1 = new Player("Devin Mourrain", MUSTARD, testHand, currentPos);
	
	//Position usage example
	std::cout << "Initial position: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;
	p1->updatePosition(std::make_tuple(1, 4));
	std::cout << "After moving: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;


	//Accessing cards within a player's hand
	std::cout << "P1's Cards before removing a card: " << std::endl;
	for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
		std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
	}

	//Removing cards example
	std::cout << "P1's Cards after removing a card: " << std::endl;
	p1->removeCard("Suspect_2");
	for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
		std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
	}

	//Notebook usage example
	p1->printNotebook();
	p1->updateNotebook(MUSTARD_N, 0, 1);
	std::cout << "===" << std::endl;
	p1->printNotebook();
	std::cout << "===" << std::endl;
	p1->updateNotebook(KITCHEN_N, 0, 1);
	p1->updateNotebook(BILLIARD_N, 0, 0);
	p1->printNotebook();
	std::cout << "===" << std::endl;

	//cardSetup();
	
	// For testing
	vector<Card*> hand1;
	hand1.push_back(new Card("Colonel Mustard", SUSPECT));
	hand1.push_back(new Card("Wrench", WEAPON));
	hand1.push_back(new Card("Lounge", ROOM));
	vector<Card*> hand2;
	hand2.push_back(new Card("Mr. Green", SUSPECT));
	hand2.push_back(new Card("Knife", WEAPON));
	hand2.push_back(new Card("Hall", ROOM));
	vector<Card*> hand3;
	hand3.push_back(new Card("Mrs. Peacock", SUSPECT));
	hand3.push_back(new Card("Lead Pipe", WEAPON));
	hand3.push_back(new Card("Ballroom", ROOM));
	vector<Card*> hand4;
	hand4.push_back(new Card("Professor Plum", SUSPECT));
	hand4.push_back(new Card("Revolver", WEAPON));
	hand4.push_back(new Card("Study", ROOM));
	vector<Card*> hand5;
	hand5.push_back(new Card("Miss Scarlet", SUSPECT));
	hand5.push_back(new Card("Candlestick", WEAPON));
	hand5.push_back(new Card("Library", ROOM));
	vector<Card*> hand6;
	hand6.push_back(new Card("Mrs. White", SUSPECT));
	hand6.push_back(new Card("Rope", WEAPON));
	hand6.push_back(new Card("Billiard Room", ROOM));

	tuple<int, int> pos1;
	tuple<int, int> pos2;
	tuple<int, int> pos3;
	tuple<int, int> pos4;
	tuple<int, int> pos5;
	tuple<int, int> pos6;

	Player player1 = Player("Player 1", MUSTARD, hand1, pos1);
	Player player2 = Player("Player 2", SCARLET, hand2, pos2);
	Player player3 = Player("Player 3", PEACOCK, hand3, pos3);
	Player player4 = Player("Player 4", GREEN, hand4, pos4);
	Player player5 = Player("Player 5", WHITE, hand5, pos5);
	Player player6 = Player("Player 6", PLUM, hand6, pos6);
	vector<Player> players = {player1, player2, player3, player4, player5, player6};

	Deck newDeck;

	vector<Card*> solution = newDeck.getSolution();
	cout << "Suspect: " << solution[0]->getName() << endl;
	cout << "Weapon: " << solution[1]->getName() << endl;
	cout << "Room: " << solution[2]->getName() << endl;

	newDeck.shuffle();

	newDeck.deal(players);
	vector<Card*> player1hand = players[0].getHand();
	vector<Card*> player2hand = players[1].getHand();
	vector<Card*> player3hand = players[2].getHand();
	vector<Card*> player4hand = players[3].getHand();
	vector<Card*> player5hand = players[4].getHand();
	vector<Card*> player6hand = players[5].getHand();

	std::cout << "Player hands:\n===" << std::endl;
	for (int i = 0; i < player1hand.size(); i++)
	{
		cout << players[0].getName() << " has " << player1hand[i]->getName() << endl;
	}
	cout << endl;
		
	for (int i = 0; i < player2hand.size(); i++)
	{
		cout << players[1].getName() << " has " << player2hand[i]->getName() << endl;
	}
	cout << endl;

	for (int i = 0; i < player3hand.size(); i++)
	{
		cout << players[2].getName() << " has " << player3hand[i]->getName() << endl;
	}
	cout << endl;

	for (int i = 0; i < player4hand.size(); i++)
	{
		cout << players[3].getName() << " has " << player4hand[i]->getName() << endl;
	}
	cout << endl;

	for (int i = 0; i < player5hand.size(); i++)
	{
		cout << players[4].getName() << " has " << player5hand[i]->getName() << endl;
	}
	cout << endl;

	for (int i = 0; i < player6hand.size(); i++)
	{
		cout << players[5].getName() << " has " << player6hand[i]->getName() << endl;
	}
	cout << endl;
	
	// Suggestion test
	vector<string> player1suggest;
	player1suggest = players[0].makeSuggestion();
	
	cout << "Player 1 has suggested:" << endl;
	cout << player1suggest[0] << " with the " << player1suggest[1] << " in the " << player1suggest[2] << endl;
	
	for (int i = 1; i < players.size(); i++) {			//currently hardcoded to start at 1 to ignore Player 1's hand, but we may want to return which player made the suggestion in the vector so we can skip them
		if (players[i].containsCard(player1suggest)) {
			//cout << players[i].getName() << " had at least one of the cards from Player 1's suggestion" << endl;
			//the point of view stuff below is somewhat trivial as all of this is global right now, but
			//minimally we have the ability to prompt a user to show a card after verifying that they have at least one card from the suggestion
			cout << "\n" << players[i].getName() << "\'s point of view: " << endl;
			string shownCard = players[i].showCard(player1suggest);
			cout << "\n==Returning from " << players[i].getName() << "\'s point of view: " << endl;			 
			cout << "The card that was shown to the player was: " << shownCard << endl;
			cout << endl;
		}
		else {
			//cout << players[i].getName() << " didn't have any cards from Player 1's suggestion" << endl;
		}
	}

	/* Game class test---not really working rn
	vector<string> player1suggest = { "Mrs. White", "Revolver", "Lounge" };
	Game newGame = Game();
	newGame.checkSuggestion(MUSTARD, player1suggest);*/

	return 0;
}