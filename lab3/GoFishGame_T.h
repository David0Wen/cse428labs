/**
 * File: GoFishGame_T.h
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Declaration of types related to an Uno deck
 */
#pragma once

#include "Suit.h"
#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "UnoDeck.h"
#include "CardSet_T.h"

template <typename S = Suit, typename R = HoldEmRank, typename D = HoldEmDeck>
class GoFishGame{
static_assert(std::is_base_of<CardSet<S, R>, D>::value,
                "Deck must be derived from CardSet<Suit, Rank>");
public:
    GoFishGame(int numPlayers, const char* playerNames[]);
    virtual ~GoFishGame();
    virtual play();
    bool collect_books(int playerNum);

protected:
    int numPlayers;
    D deck;
    std::vector<CardSet> hands;
    std::vector<CardSet> books;
    virtual deal();
    bool turn(int playerNum);
};
template<>
GoFishGame<Suit, HoldEmRank,HoldEmDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

template<>
GoFishGame<Suit, PinochleRank,PinochleDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

template<>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "GoFishGame_T.cpp"
#endif
