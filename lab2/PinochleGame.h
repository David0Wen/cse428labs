/**
* File: PinochleGame.h
* Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
* Purpose: Declaration of PinochleGame class.
*/

#ifndef _PINOCHLEGAME_H
#define _PINOCHLEGAME_H

#include <vector>
#include <string>
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"

enum class PinochleMelds {
    dix,
    offsuitmarriage,
    fortyjacks,
    pinochle,
    insuitmarriage,
    sixtyqueens,
    eightykings,
    hundredaces,
    insuitrun,
    doublepinochle,
    fourhundredjacks,
    sixhundredqueens,
    eighthundredkings,
    thousandaces,
    insuitdoublerun
};

std::ostream &operator<<(std::ostream &os, const PinochleMelds &meld);

// Class to represent a game of Pinochle
class PinochleGame : public Game {
private:
    static bool isFourSuits(const std::vector< Card<PinochleRank, Suit> >::iterator &, const std::vector< Card<PinochleRank, Suit> >::iterator &, PinochleRank);
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &, std::vector<PinochleMelds> &);
protected:
    // A deck of cards designed for Pinochle
    PinochleDeck myDeck;
    // A vector containing the hands of cards for each player
    std::vector<CardSet<PinochleRank, Suit> > playerHands;

    // Deal cards to players and advances the game state
    virtual void deal();
public:
    static const char* MeldNames[];
    static const unsigned int MeldPoints[];
    // Constructor to initialize PinochleGame object
    PinochleGame(int argc, const char *argv[]);

    // Print the cards of all players
    void printPlayersCards(std::ostream &, size_t);
    // Collect all cards back to the deck
    void roundCollect();
    // Game loop for a Pinochle game
    virtual int play();
};


#endif //_PINOCHLEGAME_H
