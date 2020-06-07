/*****************************************************************************************
 * Program Name: StartScreen.hpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: The header file for the start screen class
*****************************************************************************************/
#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include <SFML/Graphics.hpp>
#include "SimpleButton.hpp"

class StartScreen
{
	private:
		sf::Sprite logo;
		sf::Texture texture;
		SimpleButton makeServer;
		SimpleButton joinServer;

	public:
		StartScreen();
		void updateButtons(const sf::Vector2f);
		bool makeServerPressed();
		bool joinServerPressed();
		void render(sf::RenderTarget*);
};

#endif