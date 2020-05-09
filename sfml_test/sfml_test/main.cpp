#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include "clueBoard.h"
#include "token.hpp"

#include <stdlib.h>
#include <time.h>

using namespace std;
void writeToLog(string message, string variable);
bool isValidMove(boardTile current_space, boardTile target_space);
int main()
{
//graphical output section
	//creating a render window with SFML
	sf::RenderWindow window(sf::VideoMode(810, 810), "Clue!", sf::Style::Default);

	//making a matrix representing the board
	boardTile** boardArray = new boardTile * [26];
	for (int i = 0; i < 26; i++) {
		boardArray[i] = new boardTile[27];
	}


	//opening csv file to fill board data
	ifstream dataSource;
	dataSource.open("NewClueBoardCSV.csv");
	if (dataSource.fail()) {
		cout << "Failed to open csv." << endl;
		return 0;
	}
	string line, word, temp;
	int row = 0;
	int col = 0;

	//filling the board based on data from the CSV
	while (!dataSource.eof()) {
		string tempStringArray[24];
		col = 0;
		getline(dataSource, line);
		stringstream tempstream(line);
		while (getline(tempstream, word, ',')) {
			boardTile tempTile(word, row, col);
			writeToLog("Grabbed tile type:", word);
			boardArray[row][col] = tempTile;
			col++;
		}
		row++;
	}


	sf::Texture board_texture;
	if (!board_texture.loadFromFile("clueboard.png", sf::IntRect(0, 0, 500, 487)))
	{
		cout << "Cannot open clueboard.png" << endl;
	}



	sf::Sprite rendered_board;
	rendered_board.move(sf::Vector2f(155, 161.5));
	rendered_board.setTexture(board_texture);


	// dimensions of each tile on the map
	double height = 20;
	double width = 19.75;

	//making mustard colored test piece
	token mustard(sf::Color(225, 173, 1), 155 + (width * 16), 165 + (height * 22), 23, 17);
	token scarlet(sf::Color(139, 0, 0), 155 + (width * 2), 165 + (height * 6), 7, 3);
	token green(sf::Color(0, 128, 0), 155 + (width * 5), 165 + (height * 16), 17, 6);
	token plum(sf::Color(221, 160, 221), 155 + (width * 11), 165 + (height * 7), 8, 12);
	token peacock(sf::Color(0, 0, 255), 155 + (width * 19), 165 + (height * 15), 16, 20);
	token white(sf::Color(128, 128, 128), 155 + (width * 19), 165 + (height * 1), 2, 20);




	while (window.isOpen())
	{
		sf::Time move_delay = sf::seconds(0.1f);
		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Right)
					{
						if (isValidMove(boardArray[mustard.get_row()][mustard.get_col()], boardArray[mustard.get_row()][mustard.get_col() + 1])) {
							mustard.move_token(width, 0, 0, 1);
						}
					}

				if (event.key.code == sf::Keyboard::Left)
					{
						if (isValidMove(boardArray[mustard.get_row()][mustard.get_col()], boardArray[mustard.get_row()][mustard.get_col() - 1])) {
							mustard.move_token(-width, 0, 0, -1);
						}
					}

					if (event.key.code == sf::Keyboard::Down)
					{
						if (isValidMove(boardArray[mustard.get_row()][mustard.get_col()], boardArray[mustard.get_row() + 1][mustard.get_col()])) {
							mustard.move_token(0, height, 1, 0);
						}
					}

					if (event.key.code == sf::Keyboard::Up)
					{
						if (isValidMove(boardArray[mustard.get_row()][mustard.get_col()], boardArray[mustard.get_row() - 1][mustard.get_col()])) {
							mustard.move_token(0, -height, -1, 0);
						}
					}

					break;

			default:
				break;
			}
		}

		window.clear();

		window.draw(rendered_board);
		window.draw(mustard.get_token());
		window.draw(scarlet.get_token());
		window.draw(green.get_token());
		window.draw(plum.get_token());
		window.draw(peacock.get_token());
		window.draw(white.get_token());
		window.display();
		}

	for (int i = 0; i < 26; i++) {
		delete[] boardArray[i];
	}
	delete[] boardArray;
	return 0;
}

void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
}

bool isValidMove(boardTile current_space, boardTile target_space) {

	if (target_space.isPassable()) {
		if ((current_space.getTile_type() == Room && target_space.getTile_type() == Floor) || (current_space.getTile_type() == Floor && target_space.getTile_type() == Room)) {

			if (current_space.hasDoor() && target_space.hasDoor()) {

				return true;
			}
			else {

				return false;
			}
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}

}