#ifndef _CARD_T_H
#define _CARD_T_H
#include <iostream>
#include "Suit.h"

// Card strucutre: rank and suit 
template <typename T>
struct Card
{
	T myRank;
	Suit mySuit;
	Card(T, Suit);
};

// make shift operator worked for Card structure
template <typename T>
std::ostream& operator<<(std::ostream &, const Card<T> &);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Card_T.cpp"
#endif

#endif
