/**
// File: Card_T.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Implementation of template structure: card.
*/
#include "Card_T.h"

template<typename T, typename S>
Card<T, S>::Card(T argRank, S argSuit)
{
	// initialize the member variables
	myRank = argRank;
	mySuit = argSuit;
}

template<typename Suit, typename Rank>
bool CompareRank(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2)
{
	if (card1.myRank < card2.myRank || (card1.myRank == card2.myRank && card1.mySuit < card2.mySuit )){
		return true;
	}
	else return false;
}

template<typename Suit, typename Rank>
bool CompareSuit(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2)
{
	if (card1.mySuit < card2.mySuit || (card1.mySuit == card2.mySuit && card1.myRank < card1.myRank)) {
		return true;
	}
	else return false;
}


// shift operator implentation
// Output the card feature to std::ostream
// @param std::ostream & the stream you want to output to
// @param const Card<T> the object you want to output
// @return std::ostream &
template<typename T, typename S>
std::ostream& operator<<(std::ostream& os, const Card<T, S>& myCard)
{
	os << myCard.myRank << myCard.mySuit;
	return os;
}