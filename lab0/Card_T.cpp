#include "Card_T.h"

template<typename T>
Card<T>::Card(T argRank, Suit argSuit) : myRank(argRank), mySuit(argSuit)
{

}

// template<typename T>
// Card<T>::Card(T argRank, Suit argSuit)
// {
//     myRank = argRank;
//     mySuit = argSuit;
// }

template<typename T>
std::ostream &operator<<(std::ostream &os, const Card<T> &myCard)
{
    os << myCard.myRank << myCard.mySuit;
    return os;
}