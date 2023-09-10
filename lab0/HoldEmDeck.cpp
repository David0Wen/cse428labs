#include "HoldEmDeck.h"

std::ostream &operator<<(std::ostream &os, const HoldEmRank &myRank)
{
    switch (myRank)
	{
	case HoldEmRank::two:
		os << "2";
		break;

	case HoldEmRank::three:
		os << "3";
		break;

	case HoldEmRank::four:
		os << "4";
		break;

	case HoldEmRank::five:
		os << "5";
		break;

	case HoldEmRank::six:
		os << "6";
		break;
        
	case HoldEmRank::seven:
		os << "7";
		break;

	case HoldEmRank::eight:
		os << "8";
		break;

	case HoldEmRank::nine:
		os << "9";
		break;

	case HoldEmRank::ten:
		os << "10";
		break;

	case HoldEmRank::jack:
		os << "J";
		break;

	case HoldEmRank::queen:
		os << "Q";
		break;
        
	case HoldEmRank::king:
		os << "K";
		break;

	case HoldEmRank::ace:
		os << "A";
		break;
        
	case HoldEmRank::undefined:
		os << "?";
		break;
	}
    return os;
}

HoldEmRank &operator++(HoldEmRank &myRank)
{
    switch (myRank)
	{
	case HoldEmRank::two:
		myRank = HoldEmRank::three;
		break;

	case HoldEmRank::three:
		myRank = HoldEmRank::four;
		break;

	case HoldEmRank::four:
		myRank = HoldEmRank::five;
		break;

	case HoldEmRank::five:
		myRank = HoldEmRank::six;
		break;

	case HoldEmRank::six:
		myRank = HoldEmRank::seven;
		break;
        
	case HoldEmRank::seven:
		myRank = HoldEmRank::eight;
		break;

	case HoldEmRank::eight:
		myRank =HoldEmRank::nine;
		break;

	case HoldEmRank::nine:
		myRank =HoldEmRank::ten;
		break;

	case HoldEmRank::ten:
		myRank =HoldEmRank::jack;
		break;

	case HoldEmRank::jack:
		myRank = HoldEmRank::queen;
		break;

	case HoldEmRank::queen:
		myRank = HoldEmRank::king;
		break;

	case HoldEmRank::king:
		myRank = HoldEmRank::ace;
		break;

	case HoldEmRank::ace:
		myRank = HoldEmRank::undefined;
		break;

	case HoldEmRank::undefined:
		break;
	}
    return myRank;
}

HoldEmDeck::HoldEmDeck()
{
    for (HoldEmRank i = HoldEmRank::two; i != HoldEmRank::undefined; ++i)
    {
        for (Suit j = Suit::clubs; j != Suit::undefined; ++j)
        {
            Card<HoldEmRank> myCard(i, j);
            myDeck.push_back(myCard);
        }
    }
    
}

void HoldEmDeck::print(std::ostream &os)
{
    std::vector< Card<HoldEmRank> >::iterator iter = myDeck.begin();
	for(; iter != myDeck.end(); ++iter)
	{
		std::cout<<(*iter)<<" ";
		if ((*iter).mySuit == Suit::spades) {
			std::cout << std::endl;
		}
    }
}
