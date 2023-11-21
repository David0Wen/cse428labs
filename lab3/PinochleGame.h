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

// enum class for possible Pinochle melds
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

/**
* Output the melds feature to std::ostream
* @param std::ostream & the stream you want to output to
* @param const PinochleMelds &meld the object you want to output
* @return std::ostream & the reference of the input stream
*/
std::ostream &operator<<(std::ostream &os, const PinochleMelds &meld);

// Class to represent a game of Pinochle
class PinochleGame : public Game {
private:
    /**
    * @brief Checks if the vector of Cards(between start and end) has four different suit for given rank
    *
    * @return True if have four different suit
    */
    static bool isFourSuits(const std::vector<Card<PinochleRank, Suit> >::iterator &, const std::vector<Card<PinochleRank, Suit> >::iterator &, PinochleRank);
    /**
    * @brief Checks if the CardSet has several different possible melds, insert all possible melds into the given vector
    */
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &, std::vector<PinochleMelds> &);

protected:
    // A deck of cards designed for Pinochle
    PinochleDeck myDeck;
    // A vector containing the hands of cards for each player
    std::vector<CardSet<PinochleRank, Suit> > playerHands;

    // Deal cards to players and advances the game state
    virtual void deal();

public:
    // Static list, assigning all possible melds(enum) with different names
    static const char* MeldNames[];
    // Static list, assigning all possible melds(enum) with different points
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
