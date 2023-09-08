#include "Suit.h"

std::ostream &operator<<(std::ostream &os, const Suit &target)
{
	switch (target)
	{
	case Suit::clubs:
		os << "C";
		break;

	case Suit::diamonds:
		os << "D";
		break;

	case Suit::hearts:
		os << "H";
		break;

	case Suit::spades:
		os << "S";
		break;

	case Suit::undefined:
		os << "?";
		break;
	}
	return os;
}

//prefix
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