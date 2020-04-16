#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include "clueBoard.h"

using namespace std;
void writeToLog(string message, string variable);

int main() {
	boardTile** boardArray = new boardTile * [27];
	for (int i = 0; i < 25; i++) {
		boardArray[i] = new boardTile[27];
	}
	boardTile room = boardTile("r");
	boardTile floor = boardTile("f");
	boardTile wall = boardTile("w");

	ifstream dataSource;
	dataSource.open("ClueBoardCSV.csv");
	if (dataSource.fail()) {
		cout << "Failed to open csv." << endl;
		return 0;
	}
	ofstream log;
	log.open("log.txt", ofstream::out | ofstream::trunc);
	if (log.fail()) {
		cout << "Failed to open log" << endl;
		return 0;
	}
	log.close();
	string line, word, temp;
	int row = 0;
	int col = 0;
	while (!dataSource.eof()) {
		string tempStringArray[27];
		col = 0;
		getline(dataSource, line);
		writeToLog("Grabbed line of:", line);
		stringstream tempstream(line);
		while (getline(tempstream, word, ',')) {
			boardTile tempTile(word, row, col);
			writeToLog("Grabbed tile type:", word);
			boardArray[row][col] = tempTile;
			col++;
		}
		row++;
	}
	clueBoard gameBoard(boardArray);
	cout << "Board of chars: " << endl;
	gameBoard.charBoard();
	return 0;
}
void writeToLog(string message, string variable) {
	ofstream log;
	log.open("log.txt", ios::app);
	log << message << " " << variable << endl;
	log.close();
}