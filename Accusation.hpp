/********************************************************************************************
 * Program Name: Accusation.hpp
 * Date: 6/7/20
 * Author: Abigail Minchella
 * Description: The header file for the Accusation class
********************************************************************************************/
#ifndef ACCUSATION_HPP
#define ACCUSATION_HPP

#include "Suggestion.hpp"
#include "SimpleButton.hpp"

class Accusation : public Suggestion 
{
	private:
		SimpleButton yes;
		SimpleButton no;
		string room;

	public:
		Accusation(sf::Font*);
		void renderConfirmation(sf::RenderTarget*);
		void updateButtons(const sf::Vector2f);
		bool yesPressed();
		bool noPressed();

		void suggestRoom(const sf::Vector2f);
		string getRoom();
		void renderSuspects(sf::RenderTarget*);
		void renderWeapons(sf::RenderTarget*);
		void renderRooms(sf::RenderTarget*);
		void renderSuggestion(sf::RenderTarget*);
};

#endif