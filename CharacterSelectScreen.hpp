/**********************************************************************************
 * Program Name: CharacterSelectScreen.hpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: The header file for the Character select screen
**********************************************************************************/
#ifndef CHARACTERSELECT_HPP
#define CHARACTERSELECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "CharacterButton.hpp"
#include "GameClient.hpp"
using std::string;

class CharacterSelectScreen
{
	private:
		sf::Sprite logo;
		sf::Texture texture;
		sf::String input;
		sf::Text inputDisplay;
		sf::Text info;
		sf::Text players;
		CharacterButton characters[6] =
		{
			CharacterButton("Miss Scarlet", sf::Vector2f(150, 120)),
			CharacterButton("Mrs. Peacock", sf::Vector2f(500, 120)),
			CharacterButton("Mrs. White", sf::Vector2f(850, 120)),
			CharacterButton("Mr. Green", sf::Vector2f(150, 525)),
			CharacterButton("Colonel Mustard", sf::Vector2f(500, 525)),
			CharacterButton("Professor Plum", sf::Vector2f(850, 525))
		};

	public:
		CharacterSelectScreen(sf::Font*);
		string getPlayers();
		void setPlayers(string);
		void disableCharacters(string, const sf::Vector2f);
		void updateCharacters(const sf::Vector2f);
		void getUserInput(sf::Event*);
		string getName();
		void nameEntered();
		string characterPressed();
		void renderCharacters(sf::RenderTarget*);
		void renderPlayers(sf::RenderTarget*);
		void renderGetInput(sf::RenderTarget*);
};

#endif