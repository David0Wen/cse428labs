/*
// File: PinochleDeck.cpp
// Authors: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Implementation of enum class: PinochleRank, class: PinochleDeck
*/

#include "PinochleDeck.h"

// implentation operators << for PinochleRank
// Output the Rank to std::ostream
// @param std::ostream & the stream you want to output to
// @param const PinochleRank & the object you want to output
// @return std::ostream &
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

// implentation operators ++ for PinochleRank
// iterate the PinochleRank to the next
// @param PinochleRank & the object you want to increase
// @return PinochleRank &
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
	// Use prefix increment operator to traverse the enumeration types
    for (PinochleRank i = PinochleRank::nine; i != PinochleRank::undefined; ++i)
    {
        for (Suit j = Suit::clubs; j != Suit::undefined; ++j)
        {
            Card<PinochleRank> myCard(i, j);
            myDeck.push_back(myCard);
        }
    }
	
	// Loop to push the second set of cards to the deck
    for (PinochleRank i = PinochleRank::nine; i != PinochleRank::undefined; ++i)
    {
        for (Suit j = Suit::clubs; j != Suit::undefined; ++j)
        {
            Card<PinochleRank> myCard(i, j);
            myDeck.push_back(myCard);
        }
    }
    
}

// Overloaded print function for the PinochleDeck class
// Prints each card in the deck, and starts a new line after each suit of spades
void PinochleDeck::print(std::ostream &os)
{
    std::vector< Card<PinochleRank> >::iterator iter = myDeck.begin();
	for(; iter != myDeck.end(); ++iter)
	{
		std::cout<<(*iter)<<" ";
        if((*iter).mySuit == Suit::spades){
            std::cout<<std::endl;
        }
	}
}
