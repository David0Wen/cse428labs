#ifndef _DECK_H
#define _DECK_H
#include <iostream>

class Deck
{
public:
    virtual void operator<<(std::ostream&) = 0;
};

#endif