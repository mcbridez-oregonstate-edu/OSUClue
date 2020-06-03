/************************************************************************************************
 * Program Name: Suggestion.hpp
 * Date: 6/3/20
 * Author: Adam Pham (with modifications by Abigail Minchella)
 * Description: The header file for the Suggestion class.
************************************************************************************************/
#ifndef SUGGESTION_HPP
#define SUGGESTION_HPP

#include "CardButton.hpp"
#include "boardFunctions.hpp"
#include <vector>
#include <string>
using std::string;

class Suggestion
{
    private:
        vector<CardButton*> b_people;
        vector<CardButton*> b_weapons;
        vector<CardButton*> b_rooms;
        sf::Text suggestionText;
        string suspect;
        string weapon;
        string revealedCard;

    public:
        Suggestion(sf::Font*);
        void suggestSuspect(sf::Vector2f);
        void suggestWeapon(sf::Vector2f);
        void chooseRevealCard(const sf::Vector2f, string, string, string);
        string getSuspect();
        string getWeapon();
        string getRevealCard();
        void renderSuspects(sf::RenderTarget*);
        void renderWeapons(sf::RenderTarget*);
        void renderSuggestion(sf::RenderTarget*, string, string, string);
        void renderRevealChoice(sf::RenderTarget*, string, string, string);
};

#endif