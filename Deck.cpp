/**************************************************************************************
 * Program Name: Deck.cpp
 * Author: Abigail Minchella
 * Date: 5/6/20
 * Description: Creates a representation of the deck of Clue cards. Contains functions
 * for shuffling, picking a solution, and dealing the cards to the player hands
**************************************************************************************/
#include "Deck.hpp"

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

void Deck::shuffle()
{
}

void Deck::pickSolution()
{
}

void Deck::deal(Player[] players)
{
}
