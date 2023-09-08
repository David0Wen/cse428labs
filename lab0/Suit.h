#ifndef _SUIT_H
#define _SUIT_H
#include <iostream>
enum class Suit
{
	clubs, diamonds, hearts, spades, undefined
};

std::ostream &operator<<(std::ostream&, const Suit&);
Suit &operator++(Suit&);

#endif