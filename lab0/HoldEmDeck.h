/*
// File: HoldEmDeck.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of enum class: HoldEmRank, class: HoldEmDeck
*/
#ifndef _HOLDEMDECK_H
#define _HOLDEMDECK_H
#include <iostream>
#include <vector>
// include struct card as a member of HoldEmDeck
#include "Card_T.h"
// include base class deck, inhert the base method print
#include "Deck.h"

enum class HoldEmRank{
    two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, undefined
};

// define operators << and ++ used for HoldEmRank
std::ostream &operator<<(std::ostream&, const HoldEmRank&);
HoldEmRank &operator++(HoldEmRank&);

// derived from the abstract base class Deck
class HoldEmDeck: public Deck
{
private:
	// deck vector
	std::vector< Card<HoldEmRank> > myDeck;
public:
	// default constructor
	HoldEmDeck();
	void print(std::ostream &);
};

#endif