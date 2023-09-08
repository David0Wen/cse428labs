#include "PinochleDeck.h"

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

PinochleRank &operator++(PinochleRank &myRank)
{
    switch (myRank)
	{
	case PinochleRank::nine:
		myRank ==PinochleRank::jack;
		break;

	case PinochleRank::jack:
		myRank ==PinochleRank::queen;
		break;

	case PinochleRank::queen:
		myRank ==PinochleRank::king;
		break;

	case PinochleRank::king:
		myRank ==PinochleRank::ten;
		break;

	case PinochleRank::ten:
		myRank ==PinochleRank::ace;
		break;
        
	case PinochleRank::ace:
		myRank ==PinochleRank::undefined;
		break;
        
	case PinochleRank::undefined:
		break;
	}
    return myRank;
}

PinochleDeck::PinochleDeck()
{
    for (PinochleRank i = PinochleRank::nine; i != PinochleRank::undefined; ++i)
    {
        for (Suit j = Suit::clubs; j != Suit::undefined; ++j)
        {
            Card<PinochleRank> myCard(i, j);
            myDeck.push_back(myCard);
        }
    }
    
}

void PinochleDeck::print(std::ostream &os)
{
    std::vector< Card<PinochleRank> >::iterator iter = myDeck.begin();
	for(; iter != myDeck.end(); ++iter)
	{
		std::cout<<(*iter)<<" ";
        if((*iter).myRank == PinochleRank::ace){
            std::cout<<std::endl;
        }
	}
}
