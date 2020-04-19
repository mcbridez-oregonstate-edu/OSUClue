#include <iostream>
#include "Player.hpp"
#include <iomanip>


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
	Card* c5 = new Card("Place_1", PLACE);
	testHand.push_back(c5);
	Card* c6 = new Card("Place_2", PLACE);
	testHand.push_back(c6);
	std::tuple<int, int> currentPos = std::make_tuple(1, 1);

	//Using the overloaded Player constructor
	Player* p1 = new Player("Devin Mourrain", MUSTARD, testHand, currentPos, "");
	
	//Position usage example
	std::cout << "Initial position: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;
	p1->updatePosition(std::make_tuple(1, 4));
	std::cout << "After moving: " + std::to_string(std::get<0>(p1->getPosition())) + ", " + std::to_string(std::get<1>(p1->getPosition())) << std::endl;


	//Notebook usage example
	std::cout << p1->getNotebook() + "\n\n";
	p1->updateNotebook("I think Scarlet did it.");
	std::cout << p1->getNotebook() + "\n\n";
	p1->updateNotebook("Maybe she did it with the knife...");
	std::cout << p1->getNotebook() + "\n" << std::endl;

	//Accessing cards within a player's hand
	std::cout << "P1's Cards: " << std::endl;
	for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
		std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
	}

	//Removing cards example
	std::cout << "P1's Cards: " << std::endl;
	p1->removeCard("Suspect_2");
	for (std::size_t i = 0; i < (p1->getHand()).size(); i++) {
		std::cout << "\t Name: " + p1->getHand().at(i)->getName() << std::endl;
	}

	//cardSetup();
	return 0;
}