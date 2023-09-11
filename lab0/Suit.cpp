#include "Suit.h"


// make operator << can take a Suit object and print it first letter
std::ostream &operator<<(std::ostream &os, const Suit &target)
{
	switch (target)
	{
	// C for clubs
	case Suit::clubs:
		os << "C";
		break;

	//D for diamonds
	case Suit::diamonds:
		os << "D";
		break;

	//H for hearts
	case Suit::hearts:
		os << "H";
		break;

	// S for spades
	case Suit::spades:
		os << "S";
		break;

	// for the suits that undefined yet
	case Suit::undefined:
		os << "?";
		break;
	}
	return os;
}

// prefix increment operator:
// increce the variable's value (Suit class) to the next one
Suit &operator++(Suit &mySuit)
{
	switch (mySuit)
	{
	case Suit::clubs:
		mySuit = Suit::diamonds;
		break;

	case Suit::diamonds:
		mySuit = Suit::hearts;
		break;

	case Suit::hearts:
		mySuit = Suit::spades;
		break;

	case Suit::spades:
		mySuit = Suit::undefined;
		break;

	case Suit::undefined:
		break;
	}
	return mySuit;
}