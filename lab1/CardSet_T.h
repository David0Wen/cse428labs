/*
// File: CardSet_T.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of template structure: cardset, will be used as deck's base class
*/
#ifndef _CARDSET_T_H
#define _CARDSET_T_H

#include "Card_T.h"
#include <vector>

template <typename R, typename S>
class CardSet
{
protected:
	std::vector< Card<R, S> > myCardSet;
public:
	void print(std::ostream&, size_t);
	bool is_empty();
	CardSet<R, S>& operator>>(CardSet<R, S>& other);
};


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif

#endif