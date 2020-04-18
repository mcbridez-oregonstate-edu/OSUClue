#include <iostream>
#include "Player.hpp"

//#include "gameInit.hpp"


int main() {
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

	std::cout << std::get<0>(currentPos);
	Player* p1 = new Player("Devin Mourrain", MUSTARD, testHand, currentPos, "Test");
	
	//cardSetup();
	return 0;
}