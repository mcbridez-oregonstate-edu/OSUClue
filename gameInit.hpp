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


void cardSetup();

// For Testing
void swap(Card** a, Card** b);
void printCards(std::vector<Card*> hand);
int inputValidation();

#endif