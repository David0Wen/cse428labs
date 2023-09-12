/*
// File: Card_T.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Implentation of template structure: card.
*/
#include "Card_T.h"

template<typename T>
Card<T>::Card(T argRank, Suit argSuit)
{
	// initialize the member variables
	myRank = argRank;
	mySuit = argSuit;
}

// shift operator implentation
// Output the card feature to std::ostream
// @param std::ostream & the stream you want to output to
// @param const Card<T> the object you want to output
// @return std::ostream &
template<typename T>
std::ostream &operator<<(std::ostream &os, const Card<T> &myCard)
{
	os << myCard.myRank << myCard.mySuit;
	return os;
}