/******************************************************************************
 * Program Name: JoinServerScreen.hpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: The header file for the join server screen class
******************************************************************************/
#ifndef JOINSERVER_HPP
#define JOINSERVER_HPP

#include <SFML/Graphics.hpp>
#include "SimpleButton.hpp"

class JoinServerScreen
{
	private:
		sf::Sprite logo;
		sf::Texture texture;
		SimpleButton back;
		SimpleButton proceed;
		sf::Text clientInstructions;
		sf::String input;
		sf::Text inputDisplay;

	public:
		JoinServerScreen(sf::Font*);
		void updateButtons(const sf::Vector2f);
		void getUserInput(sf::Event* event);
		sf::String getIP();
		bool proceedPressed();
		bool backPressed();
		void clientCreated();
		void clientNotCreated();
		void render(sf::RenderTarget*);
};

#endif