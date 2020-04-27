/********************************************************************************
** Changes by: Adam Pham
** Date: 4/15/2020
** Description: This is the header file for the gamInit functions. The purpose of these
**				functions is to set up the game.
********************************************************************************/
#ifndef GAMEINIT
#define GAMEINIT

#include "Card.hpp"
#include <vector>
#include <map>


void cardSetup();
int accusation(std::vector<Card*>, std::map<int, Card*>);

// For Testing
void swap(Card** a, Card** b);
void printCards(std::vector<Card*> hand);
int inputValidation();

#endif