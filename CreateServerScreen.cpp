/*********************************************************************************
 * Program Name: CreateServerScreen.cpp
 * Date: 5/30/20
 * Author: Abigail Minchella
 * Description: Handles all the objects for the create server screen
*********************************************************************************/
#include "CreateServerScreen.hpp"

/*********************************************************************************
					CreateServerScreen::CreateServerScreen()
 * Description: Initializes the objects for the create server screen and puts
 * them in their correct places/formats
*********************************************************************************/
CreateServerScreen::CreateServerScreen(sf::Font* font) : back("Back", sf::Vector2f(750, 700), 75), proceed("Continue", sf::Vector2f(400, 700), 75)
{
	texture.loadFromFile("res/images/logo.jpg");
	logo.setTexture(texture);
	logo.setColor(sf::Color(255, 255, 255));
	logo.setPosition(sf::Vector2f(250, 150));
	logo.setScale(4, 4);

	instructions.setFont(*font);
	instructions.setString("Creating server...");
	instructions.setCharacterSize(70);
	instructions.setPosition(sf::Vector2f(500, 500));

	IP.setFont(*font);
	IP.setCharacterSize(60);
	IP.setPosition(sf::Vector2f(455, 575));

	proceed.disable();
}

/*********************************************************************************
			void CreateServerScreen::serverCreated(sf::IpAddress serverIP)
 * Description: If the server creation was successful, takes the server's IP 
 * and changes the instructions display to tell the user how to continue
*********************************************************************************/
void CreateServerScreen::serverCreated(sf::IpAddress serverIP)
{
	instructions.setString("Done! Share the IP address with your friends!");
	instructions.setPosition(sf::Vector2f(140, 500));
	IP.setString("Server IP: " + serverIP.toString());
	proceed.enable();
}

/*********************************************************************************
						void CreateServerScreen::serverNotCreated()
 * Description: In the event the server was not created, changes the instructions
 * to reflect that and tell the user what to do
*********************************************************************************/
void CreateServerScreen::serverNotCreated()
{
	instructions.setString("Something went wrong! Please go back and try again");
	instructions.setPosition(sf::Vector2f(75, 500));
	proceed.disable();
}

/*********************************************************************************
		void CreateServerScreen::updateButtons(const sf::Vector2f mouse)
 * Description: Updates the buttons based on the position of the mouse
*********************************************************************************/
void CreateServerScreen::updateButtons(const sf::Vector2f mouse)
{
	proceed.update(mouse);
	back.update(mouse);
}

/*********************************************************************************
						bool CreateServerScreen::proceedPressed()
 * Description: Returns true if the proceed button was pressed
*********************************************************************************/
bool CreateServerScreen::proceedPressed()
{
	return proceed.isPressed();
}

/*********************************************************************************
						bool CreateServerScreen::backPressed()
 * Description: Returns true if the back button was pressed
*********************************************************************************/
bool CreateServerScreen::backPressed()
{
	return back.isPressed();
}

/*********************************************************************************
			void CreateServerScreen::render(sf::RenderTarget* window)
 * Description: Draws the objects for the create server screen in the specified 
 * window
*********************************************************************************/
void CreateServerScreen::render(sf::RenderTarget* window)
{
	window->draw(logo);
	back.render(window);
	proceed.render(window);
	window->draw(instructions);
	window->draw(IP);
}
