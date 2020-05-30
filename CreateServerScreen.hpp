/*********************************************************************************
 * Program Name: CreateServerScreen.hpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: The header file for the create server screen
*********************************************************************************/
#ifndef CREATESERVER_HPP
#define CREATESERVER_HPP

#include <SFML/Graphics.hpp>
#include "SimpleButton.hpp"
#include "GameServer.hpp"

class CreateServerScreen
{
	private:
		sf::Sprite logo;
		sf::Texture texture;
		sf::Text instructions;
		sf::Text IP;
		SimpleButton back;
		SimpleButton proceed;

	public:
		CreateServerScreen(sf::Font*);
		void serverCreated(sf::IpAddress);
		void serverNotCreated();
		void updateButtons(const sf::Vector2f);
		bool proceedPressed();
		bool backPressed();
		void render(sf::RenderTarget*);
};

#endif