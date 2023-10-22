/**
// File: CardSet_T.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of template structure: cardset, will be used as deck's base class
*/
#ifndef _CARDSET_T_H
#define _CARDSET_T_H

// Include the Card_T which contains the Card struct
#include "Card_T.h"
#include <vector>

// Template class definition for CardSet
template <typename R, typename S>
class CardSet
{
protected:
    // A vector to hold Card objects
    std::vector< Card<R, S> > myCardSet;
public:
    // Function to print the CardSet
	void print(std::ostream&, size_t);
    // Function to check if the CardSet is empty
	bool is_empty();
    // Overloading the >> operator to perform two CardSet objects
	CardSet<R, S>& operator>>(CardSet<R, S>& other);
};


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif

#endif