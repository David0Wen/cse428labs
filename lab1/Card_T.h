/*
// File: Card_T.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of template structure: card, will be used as deck's member variable
*/

#ifndef _CARD_T_H
#define _CARD_T_H
#include <iostream>
// Include enum class suit as a member of card
#include "Suit.h"

// Card strucutre: rank and suit 
template <typename T, typename S>
struct Card
{
	T myRank;
	Suit mySuit;
	// Vaule Constructor 
	Card(T, S);
};

// shift operator declaration
// Output the card feature to std::ostream
// @param std::ostream & the stream you want to output to
// @param const Card<T> the object you want to output
// @return std::ostream &
template <typename T, typename S>
std::ostream& operator<<(std::ostream&, const Card<T, S>&);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Card_T.cpp"
#endif

#endif