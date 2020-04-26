#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

const string message = "Your turn!\nSelect your choice by entering the appropriate number:\n1. Roll\n2. Journal\n3. Quit\n";
const string invalid = "Invalid entry, please try again...\n";
int main() {
	//this section of code is intended to simulate control of a turn for a single player
	srand(time(NULL));
	int entry = 1;
	
	while (entry) {
		cout << message;
		cin.clear();
		cin >> entry;
		while (!entry) {
			cout << invalid;
			cin.clear();
		}
		int sum = 0;
		switch (entry) {
		case 1:
			sum += (rand() % 6 + 1) + (rand() % 6 + 1);
			printf("You rolled a %d!\n", sum);
			cout << "Please enter the coordinates you wish to move your character to. " << endl;
			int x, y;
			cout << "Row: ";
			cin >> y;
			cout << endl << "Column: ";
			cin >> x;
			cout << endl;
			cout << "HERE IS WHERE WE CAN PASS THE NUMBER INTO A ROUTE CHECKING FUNCTION." << endl;
			break;
		case 2:
			cout << "HERE IS WHERE WE TRIGGER THE JOURNAL FUNCTION." << endl;
			break;
		case 3:
			return 1;
		default:
			cout << "Invalid entry, please try again." << endl;
			break;
		}
	}

}