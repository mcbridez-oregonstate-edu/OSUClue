/*****************************************************************************************
 * Program Name: StartScreen.cpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: Creates a start screen for the Clue game
*****************************************************************************************/
#include "StartScreen.hpp"

/*****************************************************************************************
									StartScreen::StartScreen()
 * Description: The constructor for the start screen. Sets up the items used in the start
 * screen
*****************************************************************************************/
StartScreen::StartScreen() : makeServer("Create a Server", sf::Vector2f(440, 550), 75), joinServer("Join a Server", sf::Vector2f(475, 670), 75)
{
	texture.loadFromFile("res/images/logo.jpg");
	logo.setTexture(texture);
	logo.setColor(sf::Color(255, 255, 255));
	logo.setPosition(sf::Vector2f(250, 150));
	logo.setScale(4, 4);
}

/*****************************************************************************************
					void StartScreen::updateButtons(const sf::Vector2f mouse)
 * Description: Updates the joinserver and makeserver buttons based on the actions of the
 * mouse.
*****************************************************************************************/
void StartScreen::updateButtons(const sf::Vector2f mouse)
{
	makeServer.update(mouse);
	joinServer.update(mouse);
}

/*****************************************************************************************
							bool StartScreen::makeServerPressed()
 * Description: Returns true if the state of the makeServer button is "PRESSED"
*****************************************************************************************/
bool StartScreen::makeServerPressed()
{
	return makeServer.isPressed();
}

/*****************************************************************************************
							bool StartScreen::joinServerPressed()
 * Description: Returns true if the state of the joinServer button is "PRESSED"
*****************************************************************************************/
bool StartScreen::joinServerPressed()
{
	return joinServer.isPressed();
}

/*****************************************************************************************
					void StartScreen::render(sf::RenderTarget* window)
 * Description: Renders the objects of the start screen in the specified target window
*****************************************************************************************/
void StartScreen::render(sf::RenderTarget* window)
{
	window->draw(logo);
	joinServer.render(window);
	makeServer.render(window);
}
