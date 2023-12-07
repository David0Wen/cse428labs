/**
 * File: CardSet_T.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of template structure: cardset, will be used as deck's base class
 */
#ifndef _CARDSET_T_H
#define _CARDSET_T_H

// Include the Card_T which contains the Card struct
#include "Card_T.h"
#include <algorithm>
#include <vector>
#include <functional>

// Template class definition for CardSet
template <typename R, typename S>
class CardSet
{

protected:
    // A vector to hold Card objects
    std::vector<Card<R, S> > myCardSet;

public:

    // type specifiers for Card
    typedef Card<R, S> card_type;
    // type specifiers for Suit
    typedef S suit_type;
    // type specifiers for Rank
    typedef R rank_type;
    // type specifier for the iterator
    typedef typename std::vector<Card<R, S> >::iterator card_iter;

    // default Constructor
    CardSet() = default;
    // Copy Constructor, the default copy constructor in this case is sufficient, since it peforms deep copy towards enum class.
    CardSet(const CardSet<R, S> &) = default;

    // Function to print the CardSet
    void print(std::ostream &, size_t);
    // Function to check if the CardSet is empty
    bool is_empty();
    // Overloading the >> operator to perform two CardSet objects
    CardSet<R, S> &operator>>(CardSet<R, S> &);

//    // Get the pointer to the object's vector data member
//    static std::vector<card_type > CardSet<R, S>::* getSetPtr();
    // return an iterator to the start of myCardSet
    card_iter begin();
    // return an iterator to the end of myCardSet
    card_iter end();
    // use std::sort for the CardSet
    void sort();
    // Add cards from another CardSet
    void addCards(CardSet<R, S> &);

    // Move cards from another CardSet into this Deck
    void collect(CardSet<R, S> &);

    // Collect cards that match certain criteria
    void collect_if(CardSet<R, S> &, std::function<bool(card_type&)> );

    // Request specific Card form another CardSet
    bool request(CardSet<R, S> &, const R &);

};


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif

#endif