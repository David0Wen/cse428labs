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

// operator << implentation: Output a card's rank and suit
template<typename T>
std::ostream &operator<<(std::ostream &os, const Card<T> &myCard)
{
    os << myCard.myRank << myCard.mySuit;
    return os;
}