/*************************************************************************
 * Program Name: buttonTestMain.cpp
 * Date: 5/25/2020
 * Author: Abigail Minchella
 * Description: I'm just trying to figure out how this whole graphics 
 * thing works, honestly....
*************************************************************************/
//#include "CharacterButton.hpp"
#include "SimpleButton.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using std::cout;
using std::endl;

enum joinState { START, SERVER_CREATE, SERVER_SELECT, CHARACTER_SELECT, WAITING };

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 960), "Clue!", sf::Style::Default);

	SimpleButton button("This is a simple button", sf::Vector2f(200, 200));

	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;
		sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				default:
				{
					break;
				}
			}	
		}
		window.clear();
		button.update(mouse);
		button.render(&window);
		window.display();
	}

	/*sf::Font font;
	if (!font.loadFromFile("res/fonts/Stabillo Medium.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}

	sf::Text info;
	info.setFont(font);
	info.setCharacterSize(75);
	info.setPosition(sf::Vector2f(350, 5));

	CharacterButton scarlet("Miss Scarlet", sf::Vector2f(150, 120));
	CharacterButton peacock("Mrs. Peacock", sf::Vector2f(500, 120));
	CharacterButton white("Mrs. White", sf::Vector2f(850, 120));
	CharacterButton green("Mr. Green", sf::Vector2f(150, 525));
	CharacterButton mustard("Colonel Mustard", sf::Vector2f(500, 525));
	CharacterButton plum("Professor Plum", sf::Vector2f(850, 525));

	joinState state = START;

	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;
		sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if (state = START)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					default:
					{
						break;
					}
				}
				info.setString("CLUE!");
			}
		}
		else if (state == CHARACTER_SELECT)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					default:
					{
						break;
					}
				}
				scarlet.update(mouse);
				peacock.update(mouse);
				white.update(mouse);
				green.update(mouse);
				mustard.update(mouse);
				plum.update(mouse);
			}
		}
		window.clear();
		window.draw(info);
		scarlet.render(&window);
		peacock.render(&window);
		white.render(&window);
		green.render(&window);
		mustard.render(&window);
		plum.render(&window);
		window.display();
	}*/

	return 0;
}