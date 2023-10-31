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

// enum class for HoldEmHandRank
enum class HoldEmHandRank{
    xhigh,
    pair,
    twopair,
    threeofakind,
    straight,
    flush,
    fullhouse,
    fourofakind,
    straightflush,
    undefined
};

/**
* Output the label feature to std::ostream
* @param std::ostream & the stream you want to output to
* @param const HoldEmHandRank &handRank the object you want to output
* @return std::ostream & the reference of the input stream
*/
std::ostream &operator<<(std::ostream & , const HoldEmHandRank & );

//Derived class from Game for Hold'em poker
class HoldEmGame :public Game
{
private:
    // eval CardSet for that player's hand
    HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> &);
    static bool compareMultiSet(CardSet<HoldEmRank, Suit>& leftHand, CardSet<HoldEmRank, Suit>&, size_t, HoldEmHandRank);
    static std::tuple<size_t, HoldEmRank> extractMultiFromSet(const std::vector< Card<HoldEmRank, Suit> >&, size_t);

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
    // Static list, assigning all possible HandRank(enum) with different names
    static const char* RankNames[];
    // Constructor for the HoldEmGame class
    HoldEmGame(int argc, const char *argv[]);

    // Print each player's cards to the specified output stream
    void printPlayersCards(std::ostream &, size_t);
    // Collect cards at the end of a round
    void roundCollect();

    // Game loop for a Texas Hold'Em game
    virtual int play();

    // Nested struct to represent a player's state in the game
    struct PlayerState {
        CardSet<HoldEmRank, Suit> playerHand;
        size_t playerNameIndex;
        HoldEmHandRank handRank;

        // Constructor
        PlayerState(CardSet<HoldEmRank, Suit>, size_t, HoldEmHandRank);
    };

    friend bool operator<(const HoldEmGame::PlayerState&, const HoldEmGame::PlayerState&);
};

// Compare PlayerState non-member
bool operator<(const HoldEmGame::PlayerState&, const HoldEmGame::PlayerState&);

#endif // _HOLDEMGAME_H