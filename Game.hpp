/*********************************************************************************************
 * Class Name: Game.hpp
 * Author: Abigail Minchella
 * Date: 5/8/2020
 * Description: The header for the Game class that will create an instance of the Clue game
*********************************************************************************************/
#include "Deck.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
using std::vector;
using std::string;

#ifndef GAME_HPP
#define GAME_HPP

class Game {
    private:
        vector<Player*> players;
        vector<Card*> solution;
        Deck gameDeck;

    public:
        Game();
        void checkSuggestion(token*, vector<string>);      // Need to implement server-client architecture to make this private b/w players
        //void play();                  // Implement later with a turn system involving the player class
};

#endif