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
#include "Game.h"
#include <type_traits> // Include for std::is_base_of
#include <iterator>
#include <algorithm>

template <typename S = Suit, typename R = HoldEmRank, typename D = HoldEmDeck>
class GoFishGame : public Game 
{
    static_assert(std::is_base_of<CardSet<R, S>, D>::value, "DeckType must be derived from CardSet<RankType, SuitType>");
public:
    // default constructor
    GoFishGame(int argc, const char* argv[]);
    virtual ~GoFishGame() = default;
    virtual int play();
    /** 
     * @brief  checks if there is a 4-of-a-kind in that player's hand 
     * @param playerNum the index of the palyer
     * @return a boolean value to indicate whether or not 4 cards of the same rank were found in it
     */
    bool collect_books(int playerNum);

protected:
    int numPlayers;
    D myDeck;
    std::vector<CardSet<R, S>> playerHands;
    std::vector<CardSet<R, S>> playerBooks;
    std::vector<int> playerBooksNum;
    std::vector<int> outPlayers;

    /** 
     * @brief  implements how each player will take their turn
     * @param playerNum the index of the palyer
     * @return a boolean value to indicate whether it still remains that player's turn
     */
    bool turn(int playerNum);

    virtual void deal();
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "GoFishGame_T.cpp"
#endif
