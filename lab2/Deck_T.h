/**
 * File: Deck_T.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of abstract base class: deck.
 */
#ifndef _DECK_T_H
#define _DECK_T_H
#include <iostream>
#include "CardSet_T.h"
#include <random>
#include <algorithm>

// Template class definition for Deck
template <typename R, typename S>
class Deck: public CardSet<R, S>
{
public:
	/**
	 * @brief Shuffle the Deck of cards.
	 */
	void shuffle();

	/**
	 * @brief Collect cards from another CardSet into this Deck
	 * 
	 * @param cardSet The CardSet that collect cards
	 */
	void collect(CardSet<R, S> &);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Deck_T.cpp"
#endif

#endif