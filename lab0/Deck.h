/*
// File: Deck.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of abstract base class: deck.
*/
#ifndef _DECK_H
#define _DECK_H
#include <iostream>

// declare abstract base class for a deck of cards
class Deck
{
public:
    // virtual method print
    // @param std::ostream &
    virtual void print(std::ostream &) = 0;
};

#endif