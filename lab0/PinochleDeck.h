#ifndef _PINOCHLEDECK_H
#define _PINOCHLEDECK_H
#include <iostream>
#include <vector>
#include "Card_T.h"
#include "Deck.h"

enum class PinochleRank{
	nine, jack, queen, king, ten, ace, undefined
};

// define operators << and ++ used for PinochleRank
std::ostream &operator<<(std::ostream&, const PinochleRank&);
PinochleRank &operator++(PinochleRank&);

// define Pinochle Deck derived from Deck class
class PinochleDeck: public Deck
{
private:
	// save the info for each card
	std::vector< Card<PinochleRank> > myDeck;
public:
	// make a deck of cards
	PinochleDeck();
	// print the string corrosponding to the rank
	void print(std::ostream &);
};

#endif