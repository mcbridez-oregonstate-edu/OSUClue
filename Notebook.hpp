/**************************************************************************************
 * Program Name: Notebook.hpp
 * Author: Abigail Minchella
 * Date: 5/18/20
 * Description: The header file for the Notebook class
**************************************************************************************/
#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP

const int NUM_OTHER_PLAYERS = 5;
const int NUM_POSSIBLE_CARDS = 21;

enum Players {P1, P2, P3, P4, P5};
enum Cards {
    SCARLET, GREEN, WHITE, PEACOCK, MUSTARD, PLUM, ROPE, WRENCH, REVOLVER, PIPE,
    CANDLESTICK, KNIFE, CONSERVATORY, STUDY, LOUNGE, KITCHEN, HALL, BILLIARD,
    BALLROOM, DINING, LIBRARY
};

class Notebook
{
    private:
        bool notebook[NUM_OTHER_PLAYERS][NUM_POSSIBLE_CARDS];

    public:
        Notebook();
        void setChecked(Players, Cards);
        void setUnchecked(Players, Cards);
        void printNotebook();
};

#endif