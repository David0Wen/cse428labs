#include "Card_T.h"

template<typename T>
Card<T>::Card(T argRank, Suit argSuit)
{
    // initialize the member variables
    myRank = argRank;
    mySuit = argSuit;
}

// make operator << can get a card's rank and suit and print them
template<typename T>
std::ostream &operator<<(std::ostream &os, const Card<T> &myCard)
{
    os << myCard.myRank << myCard.mySuit;
    return os;
}