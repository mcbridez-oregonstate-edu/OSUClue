/**************************************************************************
 * Program Name: Deck.hpp
 * Author: Abigail Minchella
 * Description: The header file for the deck class. Initializes a deck of
 * Clue cards
**************************************************************************/
#include "Card.hpp"
#include "Player.hpp"

#ifndef DECK_HPP
#define DECK_HPP

class Deck {
private:
    Card[] deck;

public:
    Deck();
    void shuffle();
    void pickSolution();
    void deal(Player[]);
};

#endif // !DECK_HPP
