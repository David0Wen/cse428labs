/**
 * File: HoldEmDeck.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of enum class: HoldEmRank, class: HoldEmDeck
 */
#ifndef _HOLDEMDECK_H
#define _HOLDEMDECK_H
#include <iostream>
#include <vector>
// include struct card as a member of HoldEmDeck
#include "Card_T.h"
// include base class deck, inhert the base method print
#include "Deck_T.h"
#include "Suit.h"

enum class HoldEmRank{
	two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, undefined
};

/** 
 * @brief operators << for HoldEmRank, Output the Rank to std::ostream
 * @param std::ostream & the stream you want to output to
 * @param const HoldEmRank& the object you want to output
 * @return std::ostream &
 */
std::ostream &operator<<(std::ostream &, const HoldEmRank &);

/** 
 * @brief operators ++ for HoldEmRank, iterate the HoldEmRank to the next
 * @param HoldEmRank& the object you want to increase
 * @return HoldEmRank &
 */
HoldEmRank &operator++(HoldEmRank &);

// derived from the abstract base class Deck
class HoldEmDeck: public Deck<HoldEmRank, Suit>
{
public:
	HoldEmDeck();
};

#endif