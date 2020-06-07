/**********************************************************************************
 * Program Title: Die.cpp
 * Author: Abigail Minchella
 * Date: 7/16/19
 * Description: A simple class that models a die of any number of sides. Has a
 * roll member function that simulates a random roll of the die and returns the
 * number rolled.
**********************************************************************************/
#include "Die.hpp"
#include <cstdlib>
#include <ctime>
using std::time;
using std::srand;
using std::rand;

/**********************************************************************************
 *											Die::Die(int)
 * Description: The constructor for a Die object. Takes an int to initialize
 * the number of sides. Also seeds the random number generator for use in the
 * roll function
**********************************************************************************/
Die::Die(int inSides)
{
	// Seed RNG	
	int seed = time(0);
	srand(seed);
	sides = inSides;
}

/**********************************************************************************
 *											int Die::roll()
 * Description: Simulates a random roll of the die and returns the number
 * rolled. Adapted from Gaddis p135
**********************************************************************************/
int Die::roll()
{
	int rollValue = (rand() % sides) + 1;
	return rollValue;
}
