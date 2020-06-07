/**************************************************************************
 * Program Name: Deck.hpp
 * Author: Abigail Minchella
 * Description: The header file for the deck class. Initializes a deck of
 * Clue cards
**************************************************************************/
#include "Card.hpp"
#include "Player.hpp"
#include <vector>
using std::vector;

#ifndef DECK_HPP
#define DECK_HPP

class Deck {
private:
    vector<Card> deck;
    vector<Card> solution;
    void pickSolution();        // We only want to run this once, so make it private and put it in the constructor
    void swap(Card* a, Card* b);    // Private helper function for shuffle

public:
    Deck();
    void shuffle();
    vector<vector<Card>> deal();
    vector<Card> getSolution();
    vector<Card> getDeck();
};

#endif // !DECK_HPP
