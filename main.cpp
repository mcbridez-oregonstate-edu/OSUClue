#include <iostream>
#include "Player.hpp"
#include "Token.hpp"
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
	return 0;
}