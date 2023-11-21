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
static_assert(std::is_base_of<CardSet<S, R, D>::value,
                "Deck must be derived from CardSet<Suit, Rank>");
public:
    // default constructor
    GoFishGame(int numPlayers, const char* playerNames[]);
    virtual ~GoFishGame();
    virtual play();
    /** 
     * @brief  checks if there is a 4-of-a-kind in that player's hand 
     * @param playerNum the index of the palyer
     * @return a boolean value to indicate whether or not 4 cards of the same rank were found in it
     */
    bool collect_books(int playerNum);

protected:
    int numPlayers;
    D deck;
    std::vector<CardSet> hands;
    std::vector<CardSet> books;
    virtual deal();    

    /** 
     * @brief  implements how each player will take their turn
     * @param playerNum the index of the palyer
     * @return a boolean value to indicate whether it still remains that player's turn
     */
    bool turn(int playerNum);
};
// template specialization for HoldEmDeck
template<>
GoFishGame<Suit, HoldEmRank,HoldEmDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

// template specialization for PinochleDeck
template<>
GoFishGame<Suit, PinochleRank,PinochleDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

// template specialization for UnoDeck
template<>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int numPlayers, const char* palyerNames[]);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "GoFishGame_T.cpp"
#endif
