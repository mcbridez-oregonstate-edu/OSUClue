/**************************************************************************************
 * Program Name: Deck.cpp
 * Author: Abigail Minchella
 * Date: 5/6/20
 * Description: Creates a representation of the deck of Clue cards. Contains functions
 * for shuffling, picking a solution, and dealing the cards to the player hands
**************************************************************************************/
#include <stdlib.h>
#include <time.h>
#include "Deck.hpp"
using std::srand;
using std::rand;
using std::time;

/**************************************************************************************
                                        Deck::Deck()
 * Description: The constructor for the deck class. Initializes an array of cards of 
 * the proper names and types for a game of Clue
**************************************************************************************/
Deck::Deck()
{
    deck = { Card("Miss Scarlet", SUSPECT),
            Card("Mr. Green", SUSPECT),
            Card("Colonel Mustard", SUSPECT),
            Card("Mrs. White", SUSPECT),
            Card("Mrs. Peacock", SUSPECT),
            Card("Professor Plum", SUSPECT),
            Card("Rope", WEAPON),
            Card("Wrench", WEAPON),
            Card("Lead Pipe", WEAPON),
            Card("Knife", WEAPON),
            Card("Candlestick", WEAPON),
            Card("Revolver", WEAPON),
            Card("Lounge", ROOM),
            Card("Library", ROOM),
            Card("Ballroom", ROOM),
            Card("Billiard Room", ROOM),
            Card("Kitchen", ROOM),
            Card("Conservatory", ROOM),
            Card("Hall", ROOM),
            Card("Study", ROOM),
            Card("Dining Room", ROOM) };
}

/***************************************************************************************
                                void Deck::swap(Card* a, Card* b)
 * Description: A private helper function used in the implementation of the shuffle 
 * function. Swaps the locations of cards a and b.
***************************************************************************************/
void Deck::swap(Card* a, Card* b)
{
    Card temp = *a;
    a* = b*;
    b* = temp;
}

/***************************************************************************************
                                    void Deck::shuffle()
 * Description: Shuffles the deck array. Based on code from 
 * https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm//
****************************************************************************************/
void Deck::shuffle()
{
    int seed = time(0);
    srand(seed);
}

void Deck::pickSolution()
{
}

void Deck::deal(Player[] players)
{
}
