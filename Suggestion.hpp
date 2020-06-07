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
#include "Card.hpp"
#include <vector>
#include <string>
using std::string;

class Suggestion
{
    protected:
        vector<CardButton*> b_people;
        vector<CardButton*> b_weapons;
        vector<CardButton*> b_rooms;
        vector<CardButton*> suggestCards;
        sf::Text suggestionText;
        string suspect;
        string weapon;
        string revealedCard;
        CardButton* revealedCardButton;

    public:
        Suggestion(sf::Font*);
        void suggestSuspect(sf::Vector2f);
        void suggestWeapon(sf::Vector2f);
        void findRevealCards(string, string, string, vector<Card>);
        void chooseRevealCard(const sf::Vector2f);
        void showRevealCard(string, string);
        string getSuspect();
        string getWeapon();
        string getRevealCard();
        void renderSuspects(sf::RenderTarget*);
        void renderWeapons(sf::RenderTarget*);
        void renderSuggestion(sf::RenderTarget*, string, string, string);
        void renderRevealChoice(sf::RenderTarget*);
        void renderReveal(sf::RenderTarget*);
        void reset();
};

#endif