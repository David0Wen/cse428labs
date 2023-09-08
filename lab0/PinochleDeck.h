#ifndef _PINOCHLEDECK_H
#define _PINOCHLEDECK_H
#include <iostream>
#include <vector>
#include "Card_T.h"
#include "Deck.h"

enum class PinochleRank{
	nine, jack, queen, king, ten, ace, undefined
};

std::ostream &operator<<(std::ostream&, const PinochleRank&);
PinochleRank &operator++(PinochleRank&);

class PinochleDeck: public Deck
{
private:
	std::vector< Card<PinochleRank> > myDeck;
public:
	PinochleDeck();
	void print(std::ostream &);
};

#endif