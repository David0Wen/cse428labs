/**
 * File: HoldEmGame.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of HoldEmGame class and functions.
 */
#include "HoldEmGame.h"

const int SUCCESS = 0;

// Number of cards each player should have
const int playerCards = 2;
// Maximum number of cards on the board
const int boardMax = 5;



/**
 * @brief Constructor for the HoldEmGame class
 *
 * @param argc The number of command-line arguments
 * @param argv Array containing the command-line arguments
 */
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), myState(HoldEmState::preflop)
{
    // Calculate the number of players based on argc
    int numPlayers = argc - 2; // Subtract 2 for program name and game name

    // Initialize the hands vector with empty hands for each player
    playerHands.resize(numPlayers);
}

/**
 * @brief Deals cards to players and the board based on the current game state
 */
void HoldEmGame::deal()
{
    try
    {
        switch (myState)
        {
        case HoldEmState::preflop:
            // Deal two cards to each player
            for (int i = 0; i < playerCards; ++i)
            {
                for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
                {
                    myDeck >> *iter;
                }
            }
            //Move to next state
            myState = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            // Deal three community cards to the board
            for (int i = 0; i < 3; ++i)
            {
                myDeck >> commonBoard;
            }
            myState = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            // Deal one community card to the board
            myDeck >> commonBoard;
            myState = HoldEmState::river;
            break;
        case HoldEmState::river:
            // Deal one community card to the board
            myDeck >> commonBoard;
            myState = HoldEmState::undefined;
            break;
        default:
            // Deal with undefined states
            break;
        }
    }
    catch (const std::runtime_error &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

/**
 * @brief Prints the cards held by each player
 *
 * @param os The output stream to the player's cards be printed
 * @param length The number of cards per line when printing
 */
void HoldEmGame::printPlayersCards(std::ostream &os, size_t length)
{
    auto handIter = playerHands.begin();
    auto nameIter = playerNames.begin();
    while (nameIter != playerNames.end())
    {
        os << "Name: " << *nameIter << std::endl;
        (*handIter).print(os, length);
        os << std::endl;
        ++handIter;
        ++nameIter;
    }
}

/**
 * @brief Collects all the cards back to the deck at the end of a round
 */
void HoldEmGame::roundCollect()
{
    for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
    {
        myDeck.collect(*iter);
    }
    myDeck.collect(commonBoard);
}

/**
 * @brief Game loop for a Texas Hold'Em game
 *
 * @return An integer representing the status of the function
 */
int HoldEmGame::play()
{
    std::cout << "Welcome to Texas Hold'Em!" << std::endl;

    while (true)
    {
        // (1) call the deck's shuffle member function;
        myDeck.shuffle();
        // (2) set the value of the HoldEmState protected member variable to be HoldEmState::preflop
        myState = HoldEmState::preflop;
        // (3) call the deal member function to deal two cards to each player's hand
        deal();
        // (4) print out each player's name and the cards in their hand to the standard output stream
        printPlayersCards(std::cout, playerCards);
        // (5) call the deal member function again to deal three cards to the board member variable
        deal();
        // (6) print out the string "BOARD (flop):" and then the cards in the board member variable
        std::cout << "BOARD (flop):" << std::endl;
        commonBoard.print(std::cout, boardMax);
        // (7) call the deal member function again to deal the fourth card to the board member variable
        deal();
        // (8) print out the string "BOARD (turn):" and then the cards in the board member variable
        std::cout << "BOARD (turn):" << std::endl;
        commonBoard.print(std::cout, boardMax);
        // (9) call the deal member function again to deal the fifth and final card to the board member variable
        deal();
        // (10) print out the string "BOARD (river):" and then the cards in the board member variable
        std::cout << "BOARD (river):" << std::endl;
        commonBoard.print(std::cout, boardMax);
        // (11) (12)
        roundCollect();
        // (13) (14)
        if (askEnd(std::cin, std::cout)) {
            std::cout << "Thanks for playing Texas Hold'Em!" << std::endl;
            return SUCCESS;
        }
        std::cout << "Starting a new round..." << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, const HoldEmHandRank &handRank){
    switch (handRank) {
        case HoldEmHandRank::xhigh:
            os << "High Card";
            break;
        case HoldEmHandRank::pair:
            os << "Pair";
            break;
        case HoldEmHandRank::twopair:
            os << "Two Pair";
            break;
        case HoldEmHandRank::threeofakind:
            os << "Three of a Kind";
            break;
        case HoldEmHandRank::straight:
            os << "Straight";
            break;
        case HoldEmHandRank::flush:
            os << "Flush";
            break;
        case HoldEmHandRank::fullhouse:
            os << "Full House";
            break;
        case HoldEmHandRank::fourofakind:
            os << "Four of a Kind";
            break;
        case HoldEmHandRank::straightflush:
            os << "Straight Flush";
            break;
        case HoldEmHandRank::undefined:
            os << "Undefined";
            break;
    }
    return os;
}

// eval CardSet for that player's hand
HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> & playerHand) {

    // Create a deep copy of player's handset
    CardSet<HoldEmRank, Suit> handCopy(playerHand);

    std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
    std::vector< Card<HoldEmRank, Suit> > mySet = handCopy.*setPtr;

    // Sort by rank and then suit (if needed)
    std::sort(mySet.begin(), mySet.end(), lessRank<HoldEmRank, Suit>);
    // vector in descending order
    std::reverse(mySet.begin(), mySet.end());


    // return undefined if there are fewer or more than five cards in the hand
    if (mySet.size() != 5) {
        return HoldEmHandRank::undefined;
    }

    // return straightflush if all five cards are of the same suit and their ranks are consecutive (with the special rule that A 2 3 4 5 of the same suit and 10 J Q K A of the same suit are the lowest and highest valid straight flushes respectively, but that any hand with cards ranked K A 2 is not considered a straight flush)
    bool isSameSuit = std::all_of(mySet.begin(), mySet.end(),
                                  [&mySet](const Card<HoldEmRank, Suit>& card) {return card.mySuit == mySet[0].mySuit;});
    bool isConsecutive = true;
    for (size_t i = 1; i < mySet.size(); ++i) {
        if (static_cast<int>(mySet[i].myRank) - static_cast<int>(mySet[i - 1].myRank) != -1) {
            isConsecutive = false;
            break;
        }
    }
    // Specific Situation
    bool isLowAce = mySet[0].myRank == HoldEmRank::five && mySet[4].myRank == HoldEmRank::ace;
    bool isHighAce = mySet[0].myRank == HoldEmRank::ace && mySet[1].myRank == HoldEmRank::king;
    if (isSameSuit && (isConsecutive || isLowAce || isHighAce)) {
        return HoldEmHandRank::straightflush;
    }

    // return fourofakind if four cards have the same rank
    bool isFourOfAKind = false;
    for (size_t i = 0; i <= mySet.size() - 4; ++i) {
        if (mySet[i].myRank == mySet[i + 1].myRank &&
            mySet[i].myRank == mySet[i + 2].myRank &&
            mySet[i].myRank == mySet[i + 3].myRank) {
            isFourOfAKind = true;
            break;
        }
    }
    if (isFourOfAKind) {
        return HoldEmHandRank::fourofakind;
    }

    // return fullhouse if three cards have the same rank and the other two cards have the same rank
    bool isFullHouse = false;
    if ((mySet[0].myRank == mySet[1].myRank && mySet[1].myRank == mySet[2].myRank && mySet[3].myRank == mySet[4].myRank) ||
        (mySet[0].myRank == mySet[1].myRank && mySet[2].myRank == mySet[3].myRank && mySet[3].myRank == mySet[4].myRank)) {
        isFullHouse = true;
    }
    if (isFullHouse) {
        return HoldEmHandRank::fullhouse;
    }

    // return flush if all five cards are of the same suit
    bool isFlush = std::all_of(mySet.begin(), mySet.end(), [&mySet](const auto &card) { return card.mySuit == mySet[0].mySuit; });
    if (isFlush) {
        return HoldEmHandRank::flush;
    }

    // return straight if the ranks of the cards are consecutive (with the special rule that A 2 3 4 5 and 10 J Q K A are the lowest and highest valid straights respectively, but any hand with cards ranked K A 2 is not considered a straight)
    bool isStraight = true;
    for (int i = 0; i < 4; ++i) {
        if (static_cast<int>(mySet[i].myRank) - static_cast<int>(mySet[i + 1].myRank) != 1) {
            isStraight = false;
            break;
        }
    }
    if (!isStraight) {
        isStraight = (mySet[0].myRank == HoldEmRank::ace && mySet[1].myRank == HoldEmRank::five &&
                      mySet[2].myRank == HoldEmRank::four && mySet[3].myRank == HoldEmRank::three &&
                      mySet[4].myRank == HoldEmRank::two) ||
                     (mySet[0].myRank == HoldEmRank::ace && mySet[1].myRank == HoldEmRank::king &&
                      mySet[2].myRank == HoldEmRank::queen && mySet[3].myRank == HoldEmRank::jack &&
                      mySet[4].myRank == HoldEmRank::ten);
    }
    if (isStraight) {
        return HoldEmHandRank::straight;
    }

    // return threeofakind if three cards have the same rank and the other two cards are of different ranks than any other cards in the hand
    bool isThreeOfAKind = false;
    if ((mySet[0].myRank == mySet[1].myRank && mySet[1].myRank == mySet[2].myRank && mySet[2].myRank != mySet[3].myRank && mySet[3].myRank != mySet[4].myRank) ||
        (mySet[1].myRank == mySet[2].myRank && mySet[2].myRank == mySet[3].myRank && mySet[1].myRank != mySet[0].myRank && mySet[3].myRank != mySet[4].myRank) ||
        (mySet[2].myRank == mySet[3].myRank && mySet[3].myRank == mySet[4].myRank && mySet[2].myRank != mySet[0].myRank && mySet[0].myRank != mySet[1].myRank)) {
        isThreeOfAKind = true;
    }
    if (isThreeOfAKind) {
        return HoldEmHandRank::threeofakind;
    }

    // return twopair if two cards have the same rank and two other cards share a different rank and the fifth card is of yet another rank
    bool isTwoPair = false;
    if ((mySet[0].myRank == mySet[1].myRank && mySet[2].myRank == mySet[3].myRank && mySet[1].myRank != mySet[2].myRank && mySet[3].myRank != mySet[4].myRank) ||
        (mySet[0].myRank == mySet[1].myRank && mySet[3].myRank == mySet[4].myRank && mySet[1].myRank != mySet[2].myRank && mySet[2].myRank != mySet[3].myRank) ||
        (mySet[1].myRank == mySet[2].myRank && mySet[3].myRank == mySet[4].myRank && mySet[0].myRank != mySet[1].myRank && mySet[2].myRank != mySet[3].myRank)) {
        isTwoPair = true;
    }
    if (isTwoPair) {
        return HoldEmHandRank::twopair;
    }

    // return pair if only two cards in the hand have the same rank
    size_t pairCount = 0;
    for (int i = 0; i < 4; ++i) {
        if (mySet[i].myRank == mySet[i + 1].myRank) {
            ++pairCount;
            break;
        }
    }
    if (pairCount == 1) {
        return HoldEmHandRank::pair;
    }

    // otherwise it should return xhigh
    return HoldEmHandRank::xhigh;
}

// Constructor
HoldEmGame::PlayerState::PlayerState(const CardSet<HoldEmRank, Suit> handSet, const std::string playName, HoldEmHandRank holdRank) : playerHand(handSet), playerName(playName), handRank(holdRank) {}


//HoldEmRank findPairRank(const CardSet<HoldEmRank, Suit>& handSet) {
//
//    std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
//    std::vector< Card<HoldEmRank, Suit> > mySet = handSet.*setPtr;
//
//    for (const auto &card : mySet) {
//        int count = std::count_if(mySet.begin(), mySet.end(),
//                                  [&card](const Card<HoldEmRank, Suit>& obj) { return obj.myRank == card.myRank; });
//        if (count == 2) {
//            return card.myRank;
//        }
//    }
//
//    // no pairing was found
//    return HoldEmRank::undefined;
//}

// Compare PlayerState
bool operator<(const HoldEmGame::PlayerState &lhs, const HoldEmGame::PlayerState &rhs) {
    if (lhs.handRank < rhs.handRank) {
        return true;
    }
    if (lhs.handRank > rhs.handRank) {
        return false;
    }

//    if (lhs.handRank == HoldEmHandRank::pair && rhs.handRank == HoldEmHandRank::pair) {
//        HoldEmRank lhsPairRank = findPairRank(lhs.playerHand);
//        HoldEmRank rhsPairRank = findPairRank(rhs.playerHand);
//
//        return lhsPairRank < rhsPairRank;
//    }


    return false;
}
