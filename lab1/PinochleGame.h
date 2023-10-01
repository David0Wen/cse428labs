/*
// File: HoldEmDeck.h
// Created by Wenzel Luis on 9/28/23.
*/

#ifndef _PINOCHLEGAME_H
#define _PINOCHLEGAME_H

#include <vector>
#include <string>
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"

class PinochleGame : public Game {
protected:
    PinochleDeck myDeck;
    std::vector<CardSet<PinochleRank, Suit> > playerHands;

    virtual void deal();
public:
    PinochleGame(int argc, const char *argv[]);

    void printPlayersCards(std::ostream&, size_t);
    void roundCollect();

    virtual int play();
};


#endif //_PINOCHLEGAME_H
