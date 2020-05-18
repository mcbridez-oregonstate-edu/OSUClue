/*******************************************************************************
 * Program Name: Notebook.cpp
 * Author: Abigail Minchella
 * Date: 5/18/2020
 * Description: A simple notebook implementation using bools to indicate if an 
 * item is checked or not. Needs to be integrated into a UI
*******************************************************************************/
#include "Notebook.hpp"
#include <iostream>
using std::cout;
using std::endl;

Notebook::Notebook()
{
    for (int i = 0; i < NUM_OTHER_PLAYERS; i++)
    {
        for (int j = 0; j < NUM_POSSIBLE_CARDS; j++)
        {
            notebook[i][j] = false;
        }
    }
}

void Notebook::setChecked(Players player, Cards card)
{
    notebook[player][card] = true;
}

void Notebook::setUnchecked(Players player, Cards card)
{
    notebook[player][card] = false;
}

void Notebook::printNotebook()
{
    // Print header
    cout << "\tP1\tP2\tP3\tP4\tP5" << endl;

    // Print row header and then values for each card
    cout << "Ms. Scarlet:";
    for (int i = 0; i < NUM_OTHER_PLAYERS; i++)
    {
        cout << notebook[i][0] << "\t";
    }
    cout << endl;
}
