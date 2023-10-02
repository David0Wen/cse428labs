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

// Class to represent a game of Pinochle
class PinochleGame : public Game {
protected:
    // A deck of cards designed for Pinochle
    PinochleDeck myDeck;
    // A vector containing the hands of cards for each player
    std::vector<CardSet<PinochleRank, Suit> > playerHands;

    // Deal cards to players and advances the game state
    virtual void deal();
public:
    // Constructor to initialize PinochleGame object
    PinochleGame(int argc, const char *argv[]);

    // Print the cards of all players
    void printPlayersCards(std::ostream&, size_t);
    // Collect all cards back to the deck
    void roundCollect();
    // Game loop for a Pinochle game
    virtual int play();
};


#endif //_PINOCHLEGAME_H
