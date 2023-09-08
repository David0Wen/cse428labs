#ifndef _HOLDEMDECK_H
#define _HOLDEMDECK_H
#include <iostream>
#include <vector>
#include "Card_T.h"
#include "Deck.h"

enum class HoldEmRank{
    two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, undefined
};

std::ostream &operator<<(std::ostream&, const HoldEmRank&);
HoldEmRank &operator++(HoldEmRank&);

class HoldEmDeck: public Deck
{
private:
	std::vector< Card<HoldEmRank> > myDeck;
public:
	HoldEmDeck();
	void print(std::ostream &);
};

#endif