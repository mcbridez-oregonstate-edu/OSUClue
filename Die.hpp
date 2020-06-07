/*****************************************************************************
 * Program Title: Die.hpp
 * Author: Abigail Minchella
 *	Date: 7/16/19
 *	Description: The header file for the Die class. Outlines the structure of
 *	the Die class
*****************************************************************************/
#ifndef DIE_HPP
#define DIE_HPP

class Die
{
	protected:
		int sides;

	public:
		Die(int);
		int roll();
};
#endif
