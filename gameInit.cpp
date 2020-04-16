/********************************************************************************
** Changes by: Adam Pham
** Date: 4/15/2020
** Description: This is the implementation file for the gamInit functions. The purpose of these
**				functions is to set up the game. Currently only used for testing card creation
********************************************************************************/
#include <string>
#include <iostream>
#include "gameInit.hpp"
#include "Card.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

// Function for testing
void swap(Card** a, Card** b) {

	Card* temp = *a;
	*a = *b;
	*b = temp;
}

// Function for testing
void printCards(std::vector<Card*> hand) {
	for (int i = 0; i < hand.size(); i++) {
		std::cout << std::left << std::setw(20) << "	" + hand.at(i)->getName();
		if (hand.at(i)->getType() == WEAPON)
		{
			std::cout << std::left << std::setw(20) << "Weapon" << std::endl;
		}
		else if (hand.at(i)->getType() == SUSPECT)
		{
			std::cout << std::left << std::setw(20) << "Suspect" << std::endl;
		}
		else {
			std::cout << std::left << std::setw(20) << "Place" << std::endl;
		}
	}
}

/********************************************************************************
** Function: cardSetup()
** Description: Function that creates all the cards and shuffles them to the players.
********************************************************************************/
void cardSetup() {
	srand(time(0));

	

		// Vector to hold all cards for later use
	std::vector<Card*> allCardsVect;

		// Individual vectors for each type, used to pick 1 card of each type for the case file
	std::vector<Card*> suspectsVect;
	std::vector<Card*> weaponsVect;
	std::vector<Card*> placesVect;

	//Create cards and add to the corresponding type vector and the vector to hold all cards

		// Suspects
	Card* s1 = new Card("Colonel Mustard", SUSPECT);
	suspectsVect.push_back(s1);
	allCardsVect.push_back(s1);

	Card* s2 = new Card("Miss Scarlet", SUSPECT);
	suspectsVect.push_back(s2);
	allCardsVect.push_back(s2);

	Card* s3 = new Card("Professor Plum", SUSPECT);
	suspectsVect.push_back(s3);
	allCardsVect.push_back(s3);

	Card* s4 = new Card("Mr. Green", SUSPECT);
	suspectsVect.push_back(s4);
	allCardsVect.push_back(s4);

	Card* s5 = new Card("Mrs. White", SUSPECT);
	suspectsVect.push_back(s5);
	allCardsVect.push_back(s5);

	Card* s6 = new Card("Mrs. Peacock", SUSPECT);
	suspectsVect.push_back(s6);
	allCardsVect.push_back(s6);

		// Weapons
	Card* w1 = new Card("Rope", WEAPON);
	weaponsVect.push_back(w1);
	allCardsVect.push_back(w1);

	Card* w2 = new Card("Lead Pipe", WEAPON);
	weaponsVect.push_back(w2);
	allCardsVect.push_back(w2);

	Card* w3 = new Card("Knife", WEAPON);
	weaponsVect.push_back(w3);
	allCardsVect.push_back(w3);

	Card* w4 = new Card("Wrench", WEAPON);
	weaponsVect.push_back(w4);
	allCardsVect.push_back(w4);

	Card* w5 = new Card("Candlestick", WEAPON);
	weaponsVect.push_back(w5);
	allCardsVect.push_back(w5);

	Card* w6 = new Card("Pistol", WEAPON);
	weaponsVect.push_back(w6);
	allCardsVect.push_back(w6);

		// Place
	Card* p1 = new Card("Hall", PLACE);
	placesVect.push_back(p1);
	allCardsVect.push_back(p1);

	Card* p2 = new Card("Lounge", PLACE);
	placesVect.push_back(p2);
	allCardsVect.push_back(p2);

	Card* p3 = new Card("Dining Room", PLACE);
	placesVect.push_back(p3);
	allCardsVect.push_back(p3);

	Card* p4 = new Card("Kitchen", PLACE);
	placesVect.push_back(p4);
	allCardsVect.push_back(p4);

	Card* p5 = new Card("Ballroom", PLACE);
	placesVect.push_back(p5);
	allCardsVect.push_back(p5);

	Card* p6 = new Card("Conservatory", PLACE);
	placesVect.push_back(p6);
	allCardsVect.push_back(p6);

	Card* p7 = new Card("Billiard Room", PLACE);
	placesVect.push_back(p7);
	allCardsVect.push_back(p7);

	Card* p8 = new Card("Library", PLACE);
	placesVect.push_back(p8);
	allCardsVect.push_back(p8);

	Card* p9 = new Card("Study", PLACE);
	placesVect.push_back(p9);
	allCardsVect.push_back(p9);

	

	// Create player hands and caseFile * FOR TESTING ONLY *
	std::vector<Card*> player1;
	std::vector<Card*> player2;
	std::vector<Card*> player3;
	std::vector<Card*> player4;
	std::vector<Card*> player5;
	std::vector<Card*> player6;
	std::vector<Card*> caseFile;

	// Select cards for the Case File, one of Suspect/Weapon/Place
	int randomRoll = rand() % 6;
	caseFile.push_back(suspectsVect.at(randomRoll));
	suspectsVect.erase(suspectsVect.begin() + randomRoll); // remove card from the available pool of cards for the players

	randomRoll = rand() % 6;
	caseFile.push_back(weaponsVect.at(randomRoll));
	weaponsVect.erase(weaponsVect.begin() + randomRoll); // remove card from the available pool of cards for the players

	randomRoll = rand() % 9;
	caseFile.push_back(placesVect.at(randomRoll));
	placesVect.erase(placesVect.begin() + randomRoll); // remove card from the available pool of cards for the players

	// put remaining cards together and shuffle
	std::vector<Card*> shuffleVect;
	shuffleVect.insert(shuffleVect.end(), suspectsVect.begin(), suspectsVect.end());
	shuffleVect.insert(shuffleVect.end(), weaponsVect.begin(), weaponsVect.end());
	shuffleVect.insert(shuffleVect.end(), placesVect.begin(), placesVect.end());

	// empty vectors no longer in use
	suspectsVect.clear();
	weaponsVect.clear();
	placesVect.clear();

	// print out available player cards before shuffling
	std::cout << "Before Shuffle:" << std::endl;
	for (int i = 0; i < shuffleVect.size(); i++) {
		std::cout << "	" + shuffleVect.at(i)->getName() << std::endl;

	}

	// Fisher Yates shuffle
	for (int i = shuffleVect.size() - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(&shuffleVect.at(i), &shuffleVect.at(j));
	}

	// print out availble player cards after shuffling
	std::cout << std::endl << "After Shuffle:" << std::endl;
	for (int i = 0; i < shuffleVect.size(); i++) {
		std::cout << "	" + shuffleVect.at(i)->getName() << std::endl;

	}


	// deal one card to each player until there are no more cards left
	int cardCount = 0;
	while (cardCount < shuffleVect.size()) {
		
		switch (cardCount % 6) {

		case 0:
			player1.push_back(shuffleVect.at(cardCount));
			break;
		case 1:
			player2.push_back(shuffleVect.at(cardCount));
			break;
		case 2:
			player3.push_back(shuffleVect.at(cardCount));
			break;
		case 3:
			player4.push_back(shuffleVect.at(cardCount));
			break;
		case 4:
			player5.push_back(shuffleVect.at(cardCount));
			break;
		case 5:
			player6.push_back(shuffleVect.at(cardCount));
			break;
		}

		cardCount++;
	}

	// empty vector no longer in use
	shuffleVect.clear();


	// print out what each player has, and what is in the case file

	std::cout << std::endl << "Player 1 has: " << std::endl;
	printCards(player1);

	std::cout << std::endl << "Player 2 has: " << std::endl;
	printCards(player2);

	std::cout << std::endl << "Player 3 has: " << std::endl;
	printCards(player3);
	

	std::cout << std::endl << "Player 4 has: " << std::endl;
	printCards(player4);

	std::cout << std::endl << "Player 5 has: " << std::endl;
	printCards(player5);

	std::cout << std::endl << "Player 6 has: " << std::endl;
	printCards(player6);

	std::cout << std::endl << "Case File has: " << std::endl;
	printCards(caseFile);


	player1.clear();
	player2.clear();
	player3.clear();
	player4.clear();
	player5.clear();
	player6.clear();
	caseFile.clear();

	std::cout << std::endl << "All Cards:" << std::endl;
	for (int i = 0; i < allCardsVect.size(); i++) {
		std::cout << "	" + allCardsVect.at(i)->getName() << std::endl;
		delete allCardsVect.at(i);
	}	
	allCardsVect.clear();

	
}

