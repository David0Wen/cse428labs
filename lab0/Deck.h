#ifndef _DECK_H
#define _DECK_H
#include <iostream>

class Deck
{
public:
    virtual void print(std::ostream &) = 0;
};

#endif