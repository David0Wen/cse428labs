/**
* File: HoldEmGame.h
* Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
* Purpose: Declaration of HoldEmGame class.
*/
#ifndef _HOLDEMGAME_H
#define _HOLDEMGAME_H

#include "Game.h"
#include "HoldEmDeck.h"

// Enumeration representing the different states in a Hold'em game
enum class HoldEmState
{
	preflop,
	flop,
	turn,
	river,
	undefined
};

//Derived class from Game for Hold'em poker
class HoldEmGame :public Game
{
protected:
	HoldEmState myState;
	HoldEmDeck myDeck;
    // Vector holding the players' cards
	std::vector<CardSet<HoldEmRank, Suit> > playerHands;
    // Common board cards that are shared by all players
	CardSet<HoldEmRank, Suit> commonBoard;

    // Deals cards to the players and the board depending on the current state
	virtual void deal();
public:
    // Constructor for the HoldEmGame class
	HoldEmGame(int argc, const char *argv[]);

    // Print each player's cards to the specified output stream
	void printPlayersCards(std::ostream &, size_t);
    // Collect cards at the end of a round
	void roundCollect();

    // Game loop for a Texas Hold'Em game
	virtual int play();
};

#endif // _HOLDEMGAME_H