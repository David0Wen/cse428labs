//
// Created by Wenzel Luis on 9/28/23.
//

#ifndef LAB1_PINOCHLEGAME_H
#define LAB1_PINOCHLEGAME_H

#include <vector>
#include <string>
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"

class PinochleGame : public Game {
protected:
    PinochleDeck deck;
    std::vector<CardSet<YourEnumRank, YourEnumSuit>> playerHands;  // Replace YourEnumRank and YourEnumSuit with actual enum types

    virtual void deal();
public:
    PinochleGame(int argc, const char *argv[]);
    virtual int play();
};


#endif //LAB1_PINOCHLEGAME_H
