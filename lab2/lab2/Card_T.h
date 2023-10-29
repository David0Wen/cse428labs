/**
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
class Card
{
public:
	T myRank;
	Suit mySuit;
	// Vaule Constructor 
	Card(T, S);
};

/**
 * Compared the rank of two sets of the card
*/
template <typename T, typename S>
bool lessRank(const Card<T, S>& , const Card<T, S>&);

/**
 * Compared the suit of two sets of the card
*/
template <typename T, typename S>
bool lessSuit(const Card<T, S>& , const Card<T, S>&);

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