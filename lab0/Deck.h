#ifndef _DECK_H
#define _DECK_H
#include <iostream>

// declare abstract base class for a deck of cards
class Deck
{
public:
    // takes a reference to an ostream and has a void rerurn type
    virtual void print(std::ostream &) = 0;
};

#endif