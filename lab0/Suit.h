#ifndef _SUIT_H
#define _SUIT_H
#include <iostream>

// declare an enumerated type for the different suits
enum class Suit
{
	// undefined > spades > hearts > diamonds> clubs
	clubs, diamonds, hearts, spades, undefined
};

// define operator << and ++
std::ostream &operator<<(std::ostream&, const Suit&);
Suit &operator++(Suit&);

#endif