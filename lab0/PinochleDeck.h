/*
// File: PinochleDeck.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of enum class: PinochleRank, class: PinochleDeck
*/

#ifndef _PINOCHLEDECK_H
#define _PINOCHLEDECK_H
#include <iostream>
#include <vector>
// Include struct card as a member of PinochleDeck
#include "Card_T.h"
// Include base class deck, inherit the base method print
#include "Deck.h"

// Declare Pinochle specific card ranks
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
