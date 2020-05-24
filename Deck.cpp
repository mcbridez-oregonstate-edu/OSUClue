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
#include <SFML/Graphics.hpp>

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
    deck.push_back(new Card("Miss Scarlet", SUSPECT));
    deck.push_back(new Card("Mr. Green", SUSPECT));
    deck.push_back(new Card("Colonel Mustard", SUSPECT));
    deck.push_back(new Card("Mrs. White", SUSPECT));
    deck.push_back(new Card("Mrs. Peacock", SUSPECT));
    deck.push_back(new Card("Professor Plum", SUSPECT));
    deck.push_back(new Card("Rope", WEAPON));
    deck.push_back(new Card("Wrench", WEAPON));
    deck.push_back(new Card("Lead Pipe", WEAPON));
    deck.push_back(new Card("Knife", WEAPON));
    deck.push_back(new Card("Candlestick", WEAPON));
    deck.push_back(new Card("Revolver", WEAPON));
    deck.push_back(new Card("Lounge", ROOM));
    deck.push_back(new Card("Library", ROOM));
    deck.push_back(new Card("Ballroom", ROOM));
    deck.push_back(new Card("Billiard Room", ROOM));
    deck.push_back(new Card("Kitchen", ROOM));
    deck.push_back(new Card("Conservatory", ROOM));
    deck.push_back(new Card("Hall", ROOM));
    deck.push_back(new Card("Study", ROOM));
    deck.push_back(new Card("Dining Room", ROOM));
    pickSolution();
}

/***************************************************************************************
                                    Deck::~Deck()
 * Description: The destructor for the Deck class. Frees all the allocated memory
***************************************************************************************/
Deck::~Deck()
{
    vector<Card*>::reverse_iterator deleteMe = deck.rbegin();
    while (deleteMe != deck.rend())
    {
        delete *deleteMe;
        deleteMe++;
    }
    deck.clear();

    deleteMe = solution.rbegin();
    while (deleteMe != solution.rend())
    {
        delete *deleteMe;
        deleteMe++;
    }
    solution.clear();
}

/***************************************************************************************
                                void Deck::swap(Card** a, Card** b)
 * Description: Swaps the locations of card a and b in the deck. A helper function for
 * shuffle
***************************************************************************************/
void Deck::swap(Card** a, Card** b)
{
    Card* temp = *a;
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
vector<Card*> Deck::getSolution()
{
    return solution;
}


/******************************************************************************************
                                    void Deck::deal(vector<Player> players)
 * Description: Continues to deal cards to the players and remove them from the deck until
 * the deck is empty
******************************************************************************************/
void Deck::deal(vector<Player*> players)
{
    int playerNum = 0;
    vector<Card*>::reverse_iterator itr = deck.rbegin();
    while (itr != deck.rend())
    {
        if (playerNum >= 6)
        {
            playerNum = 0;
        }
        players[playerNum]->addCard(*itr);
        playerNum++;
        itr++;
    }
}

/*******************************************************************************************
                                    void Deck::pickSolution()
 * Description: Picks a random solution from the deck and stores it in its own vector.
 * Removes the cards from the deck upon adding to the solution.
*******************************************************************************************/
void Deck::pickSolution()
{
    vector<Card*>::iterator itr = deck.begin();

    // Seed RNG
    int seed = time(0);
    srand(seed);

    // Pick a suspect at random, add to the solution, and remove from main deck
    int susVal = rand() % 6;     // Gives a number 0-5 (current suspect positions)
    Card* suspect = new Card(deck[susVal]->getName(), deck[susVal]->getType());
    solution.push_back(suspect);
    advance(itr, susVal);
    delete *itr;
    deck.erase(itr);

    // Pick a weapon at random, add to solution, and remove from the main deck
    int weapVal= (rand() % 6) + 5;      // Gives a number 5-10 (current weapon positions after removal of 1 suspect)
    Card* weapon = new Card(deck[weapVal]->getName(), deck[weapVal]->getType());
    solution.push_back(weapon);
    itr = deck.begin();
    advance(itr, weapVal);
    delete *itr;
    deck.erase(itr);

    // Pick a room at random, add to solution, and remove from the main deck
    int roomVal = (rand() % 9) + 10;        // Gives a number 10-19 (current room positions after removal of weapon and suspect)
    Card* room = new Card(deck[roomVal]->getName(), deck[roomVal]->getType());
    solution.push_back(room);
    itr = deck.begin();
    advance(itr, roomVal);
    delete *itr;
    deck.erase(itr);
}
