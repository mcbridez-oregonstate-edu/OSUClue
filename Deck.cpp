/**************************************************************************************
 * Program Name: Deck.cpp
 * Author: Abigail Minchella
 * Date: 5/6/20
 * Description: Creates a representation of the deck of Clue cards. Contains functions
 * for shuffling, picking a solution, and dealing the cards to the player hands
**************************************************************************************/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Deck.hpp"
using std::srand;
using std::rand;
using std::cout;
using std::endl;

/**************************************************************************************
                                        Deck::Deck()
 * Description: The constructor for the deck class. Initializes an array of cards of 
 * the proper names and types for a game of Clue
**************************************************************************************/
Deck::Deck()
{
    deck.push_back(Card("Miss Scarlet", SUSPECT));
    deck.push_back(Card("Mr. Green", SUSPECT));
    deck.push_back(Card("Colonel Mustard", SUSPECT));
    deck.push_back(Card("Mrs. White", SUSPECT));
    deck.push_back(Card("Mrs. Peacock", SUSPECT));
    deck.push_back(Card("Professor Plum", SUSPECT));
    deck.push_back(Card("Rope", WEAPON));
    deck.push_back(Card("Wrench", WEAPON));
    deck.push_back(Card("Lead Pipe", WEAPON));
    deck.push_back(Card("Knife", WEAPON));
    deck.push_back(Card("Candlestick", WEAPON));
    deck.push_back(Card("Revolver", WEAPON));
    deck.push_back(Card("Lounge", ROOM));
    deck.push_back(Card("Library", ROOM));
    deck.push_back(Card("Ballroom", ROOM));
    deck.push_back(Card("Billiard Room", ROOM));
    deck.push_back(Card("Kitchen", ROOM));
    deck.push_back(Card("Conservatory", ROOM));
    deck.push_back(Card("Hall", ROOM));
    deck.push_back(Card("Study", ROOM));
    deck.push_back(Card("Dining Room", ROOM));

    pickSolution();
    shuffle();
}

/***************************************************************************************
                                void Deck::swap(Card* a, Card* b)
 * Description: Swaps the locations of card a and b in the deck. A helper function for
 * shuffle
***************************************************************************************/
void Deck::swap(Card* a, Card* b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}

/***************************************************************************************
                                    void Deck::shuffle()
 * Description: Shuffles the deck array. Based on code from 
 * https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm//
****************************************************************************************/
void Deck::shuffle()
{
    // Seed RNG
    int seed = time(0);
    srand(seed);

    for (int i = 17; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&deck.at(i), &deck.at(j));
    }
}

/******************************************************************************************
                                   vector<Card> Deck::getSolution()
 * Description: Returns the solution vector to the calling function
******************************************************************************************/
vector<Card> Deck::getSolution()
{
    return solution;
}

/******************************************************************************************
                                 vector<Card> Deck::getDeck()
 * Description: Returns the deck vector to the calling function
******************************************************************************************/
vector<Card> Deck::getDeck()
{
    return deck;
}

/******************************************************************************************
                           vector<vector<Card*>> Deck::deal()
 * Description: Deals cards to a vector of hands, then returns the vector, to be 
 * distributed by the server
******************************************************************************************/
vector<vector<Card>> Deck::deal()
{
    int playerNum = 0;

    vector<vector<Card>> hands;
    vector<Card> p1Hand;
    vector<Card> p2Hand;
    vector<Card> p3Hand;
    vector<Card> p4Hand;
    vector<Card> p5Hand;
    vector<Card> p6Hand;
    hands.push_back(p1Hand);
    hands.push_back(p2Hand);
    hands.push_back(p3Hand);
    hands.push_back(p4Hand);
    hands.push_back(p5Hand);
    hands.push_back(p6Hand);

    vector<Card>::reverse_iterator itr = deck.rbegin();
    while (itr != deck.rend())
    {
        if (playerNum >= 6)
        {
            playerNum = 0;
        }
        hands[playerNum].push_back(*itr);
        playerNum++;
        itr++;
    }

    return hands;
}

/*******************************************************************************************
                                    void Deck::pickSolution()
 * Description: Picks a random solution from the deck and stores it in its own vector.
 * Removes the cards from the deck upon adding to the solution.
*******************************************************************************************/
void Deck::pickSolution()
{
    vector<Card>::iterator itr = deck.begin();

    // Seed RNG
    int seed = time(0);
    srand(seed);

    // Pick a suspect at random, add to the solution, and remove from main deck
    int susVal = rand() % 6;     // Gives a number 0-5 (current suspect positions)
    Card suspect(deck[susVal].getName(), deck[susVal].getType());
    solution.push_back(suspect);
    advance(itr, susVal);
    deck.erase(itr);

    // Pick a weapon at random, add to solution, and remove from the main deck
    int weapVal= (rand() % 6) + 5;      // Gives a number 5-10 (current weapon positions after removal of 1 suspect)
    Card weapon(deck[weapVal].getName(), deck[weapVal].getType());
    solution.push_back(weapon);
    itr = deck.begin();
    advance(itr, weapVal);
    deck.erase(itr);

    // Pick a room at random, add to solution, and remove from the main deck
    int roomVal = (rand() % 9) + 10;        // Gives a number 10-19 (current room positions after removal of weapon and suspect)
    Card room(deck[roomVal].getName(), deck[weapVal].getType());
    solution.push_back(room);
    itr = deck.begin();
    advance(itr, roomVal);
    deck.erase(itr);
}
