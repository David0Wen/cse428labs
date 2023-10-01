/*
// File: HoldEmGame.h
// Author: Ruoyao Wen ruoyao@wustl.edu
*/
#ifndef _HOLDEMGAME_H
#define _HOLDEMGAME_H

#include "Game.h"
#include "HoldEmDeck.h"

enum class HoldEmState
{
	preflop,
	flop,
	turn,
	river,
	undefined
};

class HoldEmGame :public Game
{
protected:
	HoldEmState myState;
	HoldEmDeck myDeck;
	std::vector<CardSet<HoldEmRank, Suit> > playerHands;
	CardSet<HoldEmRank, Suit> commonBoard;

	virtual void deal();
public:
	HoldEmGame(int argc, const char *argv[]);

	void printPlayersCards(std::ostream&, size_t);
	void roundCollect();

	virtual int play();
};

#endif // _HOLDEMGAME_H