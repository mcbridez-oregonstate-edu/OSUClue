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
#include <map>
#include <ctime>
#include <cstdlib>
#include <iomanip>


/********************************************************************************
** Function: cardSetup()
** Description: Function that creates all the cards and shuffles them to the players.
********************************************************************************/
void cardSetup() {
	srand(time(0));

	

		// Vector to hold all cards for later use
	//std::vector<Card*> allCardsVect;
	std::map<int, Card*> allCards;

		// Individual vectors for each type, used to pick 1 card of each type for the case file
	std::vector<Card*> suspectsVect;
	std::vector<Card*> weaponsVect;
	std::vector<Card*> placesVect;

	//Create cards and add to the corresponding type vector and the vector to hold all cards

		// Suspects
	Card* s1 = new Card("Colonel Mustard", SUSPECT);
	suspectsVect.push_back(s1);
	allCards.insert({ 1, s1 });

	Card* s2 = new Card("Miss Scarlet", SUSPECT);
	suspectsVect.push_back(s2);
	allCards.insert({ 2, s2 });

	Card* s3 = new Card("Professor Plum", SUSPECT);
	suspectsVect.push_back(s3);
	allCards.insert({ 3, s3 });

	Card* s4 = new Card("Mr. Green", SUSPECT);
	suspectsVect.push_back(s4);
	allCards.insert({ 4, s4 });

	Card* s5 = new Card("Mrs. White", SUSPECT);
	suspectsVect.push_back(s5);
	allCards.insert({ 5, s5 });

	Card* s6 = new Card("Mrs. Peacock", SUSPECT);
	suspectsVect.push_back(s6);
	allCards.insert({ 6, s6 });

		// Weapons
	Card* w1 = new Card("Rope", WEAPON);
	weaponsVect.push_back(w1);
	allCards.insert({ 7, w1 });

	Card* w2 = new Card("Lead Pipe", WEAPON);
	weaponsVect.push_back(w2);
	allCards.insert({ 8, w2 });

	Card* w3 = new Card("Knife", WEAPON);
	weaponsVect.push_back(w3);
	allCards.insert({ 9, w3 });

	Card* w4 = new Card("Wrench", WEAPON);
	weaponsVect.push_back(w4);
	allCards.insert({ 10, w4 });

	Card* w5 = new Card("Candlestick", WEAPON);
	weaponsVect.push_back(w5);
	allCards.insert({ 11, w5 });

	Card* w6 = new Card("Pistol", WEAPON);
	weaponsVect.push_back(w6);
	allCards.insert({ 12, w6 });

		// Place
	Card* p1 = new Card("Hall", PLACE);
	placesVect.push_back(p1);
	allCards.insert({ 13, p1 });

	Card* p2 = new Card("Lounge", PLACE);
	placesVect.push_back(p2);
	allCards.insert({ 14, p2 });

	Card* p3 = new Card("Dining Room", PLACE);
	placesVect.push_back(p3);
	allCards.insert({ 15, p3 });

	Card* p4 = new Card("Kitchen", PLACE);
	placesVect.push_back(p4);
	allCards.insert({ 16, p4 });

	Card* p5 = new Card("Ballroom", PLACE);
	placesVect.push_back(p5);
	allCards.insert({ 17, p5 });

	Card* p6 = new Card("Conservatory", PLACE);
	placesVect.push_back(p6);
	allCards.insert({ 18, p6 });

	Card* p7 = new Card("Billiard Room", PLACE);
	placesVect.push_back(p7);
	allCards.insert({ 19, p7 });

	Card* p8 = new Card("Library", PLACE);
	placesVect.push_back(p8);
	allCards.insert({ 20, p8 });

	Card* p9 = new Card("Study", PLACE);
	placesVect.push_back(p9);
	allCards.insert({ 21, p9 });

	/*
		allCards map 
		Key	|	Value(Card)
		1		Colonel Mustard
		2		Miss Scarlet
		3		Proffesor Plum
		4		Mr. Green
		5		Mrs. White
		6		Mrs. Peacock
		7		Rope
		8		Lead Pipe
		9		Knife
		10		Wrench
		11		Candelstick
		12		Pistol
		13		Hall
		14		Lounge
		15		Dining Room
		16		Kitchen
		17		Ballroom
		18		Conservatory
		19		Billiard Room
		20		Library
		21		Study
	*/

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

	std::cout << "Shuffling all cards!" << std::endl;

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
	
	std::cout << std::endl;
	std::cout << "All cards have been dealt to the player and the case file." << std::endl;

	
// Test for shuffling/dealing/accusations
	int choice = 0;

	do {
		std::cout << std::endl;
		std::cout << "What would you like to do? (Enter the number of your choice)" << std::endl;
		std::cout << "\t 1. Print all hands and case file" << std::endl;
		std::cout << "\t 2. Make an accusation" << std::endl;
		std::cout << "\t 3. Quit" << std::endl;

		choice = inputValidation(); // get int input for user

		system("CLS");

		if (choice < 1 || choice > 3) {
			std::cout << "OOPS! That's not one of the choices! Try again." << std::endl;
		}
		else if (choice == 1) {

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

		}

		// user chooses to make an accusation
		else if (choice == 2) {
			if (accusation(caseFile, allCards)) {
				std::cout << "Congratulations! You solved the murder!" << std::endl;
			}
			else {
				std::cout << "The murderer got away." << std::endl;
			}
		}

	} while (choice != 3); // loop until user exits;

	std::cout << "Goodbye!" << std::endl;

	// free memory
	for (std::map<int, Card*>::iterator it = allCards.begin(); it != allCards.end(); ++it){
		delete it->second;
	}
	allCards.clear();
	
}

/********************************************************************************
** Function: int accusation(vector<Card*>, map<int, Card*>)
** Description: Function that simulates the accusation action. Takes the caseFile
**				as an argument and builds another vector containing suspect/location/weapon
**				cards and compares it to the caseFile. Returns 1 if the accusastion
**				is correct and 0 otherwise
********************************************************************************/
int accusation(std::vector<Card*> caseFile, std::map<int, Card*> allCards) {
	// builds a vector containg pointers to the player's guess and compares that vector with case file
	int guess = 0;
	std::vector<Card*> accusationVect;

	do {
		std::cout << "Choose a Suspect:" << std::endl;
		std::cout << "\t 1. Colonel Mustard" << std::endl;
		std::cout << "\t 2. Miss Scarlet" << std::endl;
		std::cout << "\t 3. Proffesor Plum" << std::endl;
		std::cout << "\t 4. Mr. Green" << std::endl;
		std::cout << "\t 5. Mrs White" << std::endl;
		std::cout << "\t 6. Mrs. Peacock" << std::endl;
		guess = inputValidation();

		if (guess < 1 || guess > 6) {
			std::cout << "OOPS! That wasn't one of the choices! Try again." << std::endl;
		}
		else {
			accusationVect.push_back(allCards.at(guess));
		}
	} while (guess < 1 || guess > 6);

	system("CLS");

	do {
		std::cout << "Choose a Weapon:" << std::endl;
		std::cout << "\t 1. Rope" << std::endl;
		std::cout << "\t 2. Lead Pipe" << std::endl;
		std::cout << "\t 3. Knife" << std::endl;
		std::cout << "\t 4. Wrench" << std::endl;
		std::cout << "\t 5. Candlestick" << std::endl;
		std::cout << "\t 6. Pistol" << std::endl;
		guess = inputValidation() + 6;

		if (guess < 7 || guess > 12) {
			std::cout << "OOPS! That wasn't one of the choices! Try again." << std::endl;
		}
		else {
			accusationVect.push_back(allCards.at(guess));
		}
	} while (guess < 7 || guess > 12);

	system("CLS");


	do {
		std::cout << "Choose a Location:" << std::endl;
		std::cout << "\t 1. Hall" << std::endl;
		std::cout << "\t 2. Lounge" << std::endl;
		std::cout << "\t 3. Dining Room" << std::endl;
		std::cout << "\t 4. Kitchen" << std::endl;
		std::cout << "\t 5. Ballroom" << std::endl;
		std::cout << "\t 6. Conservatory" << std::endl;
		std::cout << "\t 7. Billiard Room" << std::endl;
		std::cout << "\t 8. Library" << std::endl;
		std::cout << "\t 9. Study" << std::endl;
		guess = inputValidation() + 12;

		if (guess < 13 || guess > 21) {
			std::cout << "OOPS! That wasn't one of the choices! Try again." << std::endl;
		}
		else {
			accusationVect.push_back(allCards.at(guess));
		}
	} while (guess < 13 || guess > 21);

	std::cout << "You chose: " << std::endl;
	printCards(accusationVect);

	// compare accusation with case file
	std::cout << std::endl;
	if (accusationVect == caseFile) {
		return 1;
	}
	else {
		return 0;
	}

	accusationVect.clear();
}
/************************************************ Functions for testing *****************************************/
void swap(Card** a, Card** b) {

	Card* temp = *a;
	*a = *b;
	*b = temp;
}


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
** Function: int inputValidation()
** Description: Function that takes a user's input. If the input is not an integer,
**              function will loop until an integer is inputted. When an integer
**              is inputted, function returns the input.
********************************************************************************/
int inputValidation()
{
	bool isValid;
	int choice;
	std::string input;
	size_t numberConverted = 0;
	size_t* pointerToConverted = &numberConverted;

	do {

		isValid = true;
		std::getline(std::cin, input);

		try {
			choice = stoi(input, pointerToConverted);
		}
		catch (std::invalid_argument & e) {

			isValid = false;
		}
		catch (std::out_of_range & e) {

			isValid = false;
		}
		if (numberConverted != input.length())  // checks if the number of characters converted to ints is
		{                                       // equal to the number of characters in the string
			isValid = false;
		}

		if (isValid == false)
		{
			std::cout << "The input was invalid! Try again." << std::endl;
		}
	} while (!isValid); // loop until valid input

	return choice;
}