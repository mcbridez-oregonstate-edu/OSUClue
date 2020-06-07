/*****************************************************************************************
 * Program Name: Sidebar.hpp
 * Date: 6/6/20
 * Author: Abigail Minchella
 * Description: The header file for the Sidebar class
*****************************************************************************************/
#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include "SimpleButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

class Sidebar
{
	private:
		SimpleButton accuse;
		SimpleButton secretPassage;
		SimpleButton endTurn;
		sf::Sprite characterImage;
		sf::Texture characterTexture;
		sf::Text playerName;

	public:
		Sidebar(sf::Font*, string, string);
		void updateButtons(const sf::Vector2f);
		void render(sf::RenderTarget*);
		void enablePassage(bool);
		void enableEndTurn(int, bool);
		void disableButtons(bool);
		bool accusePressed();
		bool passagePressed();
		bool endTurnPressed();
		void resetAccuse();
};

#endif