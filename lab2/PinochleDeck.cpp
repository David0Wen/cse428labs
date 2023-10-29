/**
 * File: PinochleDeck.cpp
 * Authors: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of enum class: PinochleRank, class: PinochleDeck
 */

#include "PinochleDeck.h"

/** 
 * @brief implentation operators << for PinochleRank, Output the Rank to std::ostream
 * @param os the stream you want to output to
 * @param myRank the object you want to output
 * @return the reference of the input ostream
 */
std::ostream &operator<<(std::ostream &os, const PinochleRank &myRank)
{
    switch (myRank)
    {
    case PinochleRank::nine:
        os << "9";
        break;

    case PinochleRank::jack:
        os << "J";
        break;

    case PinochleRank::queen:
        os << "Q";
        break;

    case PinochleRank::king:
        os << "K";
        break;

    case PinochleRank::ten:
        os << "10";
        break;
        
    case PinochleRank::ace:
        os << "A";
        break;
        
    case PinochleRank::undefined:
        os << "?";
        break;
    }
    return os;
}

/** 
 * @brief implentation operators ++ for PinochleRank, iterate the PinochleRank to the next
 * @param myRank the object you want to increase
 * @return the reference of the PinochleRank after increase
 */
PinochleRank &operator++(PinochleRank &myRank)
{
    switch (myRank)
    {
    case PinochleRank::nine:
        myRank = PinochleRank::jack;
        break;

    case PinochleRank::jack:
        myRank = PinochleRank::queen;
        break;

    case PinochleRank::queen:
        myRank = PinochleRank::king;
        break;

    case PinochleRank::king:
        myRank = PinochleRank::ten;
        break;

    case PinochleRank::ten:
        myRank = PinochleRank::ace;
        break;
        
    case PinochleRank::ace:
        myRank = PinochleRank::undefined;
        break;
        
    // remain the same
    case PinochleRank::undefined:
        break;
    }
    return myRank;
}

// Default constructor for the PinochleDeck class
// Initializes the deck with cards from 9 to Ace for each suit, and does this twice since a Pinochle deck contains two copies of each card
PinochleDeck::PinochleDeck()
{
    for (PinochleRank i = PinochleRank::nine; i != PinochleRank::undefined; ++i)
    {
        for (Suit j = Suit::clubs; j != Suit::undefined; ++j)
        {
            Card<PinochleRank, Suit> myCard(i, j);
            myCardSet.push_back(myCard);
            Card<PinochleRank, Suit> myCard2(i, j);
            myCardSet.push_back(myCard2);
        }
    }
}
