/**
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
#include "Deck_T.h"
#include "Suit.h"

// Declare Pinochle specific card ranks
enum class PinochleRank{
	nine, jack, queen, king, ten, ace, undefined
};

// define operators << for PinochleRank
// Output the Rank to std::ostream
// @param std::ostream & the stream you want to output to
// @param const PinochleRank& the object you want to output
// @return std::ostream &
std::ostream &operator<<(std::ostream &, const PinochleRank &);

// define operators ++ for PinochleRank
// iterate the PinochleRank to the next
// @param PinochleRank& the object you want to increase
// @return PinochleRank&
PinochleRank &operator++(PinochleRank &);

// define Pinochle Deck derived from Deck class
class PinochleDeck: public Deck<PinochleRank, Suit>
{
public:
	// make a deck of cards
	PinochleDeck();
};

#endif
