/**
 * File: Card_T.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of template structure: card.
 */
#include "Card_T.h"

template<typename T, typename S>
Card<T, S>::Card(T argRank, S argSuit)
{
	// initialize the member variables
	myRank = argRank;
	mySuit = argSuit;
}

/** 
 * @brief operator declaration, Output the card feature to std::ostream
 * @param os the stream you want to output to
 * @param myCard the object you want to output
 * @return std::ostream &
 */
template<typename T, typename S>
std::ostream &operator<<(std::ostream &os, const Card<T, S> &myCard)
{
	os << myCard.myRank << myCard.mySuit;
	return os;
}

template<typename T, typename S>
bool lessRank(const Card<T, S> &card1, const Card<T, S> &card2)
{
	if (card1.myRank < card2.myRank || (card1.myRank == card2.myRank && card1.mySuit < card2.mySuit)){
		return true;
	}
	
	return false;
}

template<typename T, typename S>
bool lessSuit(const Card<T, S> &card1, const Card<T, S> &card2)
{
	if (card1.mySuit < card2.mySuit || (card1.mySuit == card2.mySuit && card1.myRank < card1.myRank)) {
		return true;
	}
	
	return false;
}
