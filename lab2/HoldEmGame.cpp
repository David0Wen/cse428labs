/**
 * File: HoldEmGame.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of HoldEmGame class and functions.
 */
#include "HoldEmGame.h"
#include <tuple>

const int SUCCESS = 0;

// Number of cards each player should have
const int playerCards = 2;
// Number of cards dealed when flop
const int flopCards = 3;
// Maximum number of cards on the board
const int boardMax = 5;


// Static list, assigning all possible melds(enum) with different names
const char* HoldEmGame::RankNames[] = {
    "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
    "Flush", "Full House", "Four of a Kind", "Straight Flush", "Undefined"
};

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
            for (int i = 0; i < flopCards; ++i)
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
        std::cout << std::endl << std::endl;

        // 6.1 declare a vector of the nested struct type PlayerState
        std::vector<PlayerState> playerHandInfos;
        // 6.2 initialize the vector with each player's information to playerHandInfos
        for (size_t i = 0; i < playerHands.size(); ++i) {
            PlayerState info(playerHands[i], i, HoldEmHandRank::undefined);
            playerHandInfos.push_back(info);
        }

        // Iterate through the vector to perform hand evaluation
        for (auto &playerState : playerHandInfos)
        {
            // Combine the player's hand with the common board
            std::vector<Card<HoldEmRank, Suit>>* playerSetPtr = &(playerState.playerHand.*CardSet<HoldEmRank, Suit>::getSetPtr());
            std::vector<Card<HoldEmRank, Suit>>* boardSetPtr = &(commonBoard.*CardSet<HoldEmRank, Suit>::getSetPtr());

            // Combine the player's hand with the common board
            playerSetPtr->insert(playerSetPtr->end(), boardSetPtr->begin(), boardSetPtr->end());

            // Evaluate the hand using hand evaluation function
            HoldEmHandRank rank = holdem_hand_evaluation(playerState.playerHand);

            // Update the player's hand rank
            playerState.handRank = rank;
        }

        // Sort the Card in each playerHand
        for (auto &playerState : playerHandInfos) {
            std::vector<Card<HoldEmRank, Suit>>* playerSetPtr = &(playerState.playerHand.*CardSet<HoldEmRank, Suit>::getSetPtr());

            std::sort(playerSetPtr->begin(), playerSetPtr->end(), lessRank<HoldEmRank, Suit>);
            std::reverse(playerSetPtr->begin(), playerSetPtr->end());
        }

        // Sort the playerStates vector based on hand rank
        std::sort(playerHandInfos.begin(), playerHandInfos.end(), [](const PlayerState &a, const PlayerState &b)
        {
            return a < b;
        });
        std::reverse(playerHandInfos.begin(), playerHandInfos.end());

        // Print sorted player details
        std::cout << "Ranking of players and cards:" << std::endl;
        for (auto &playerState : playerHandInfos)
        {
            std::cout << "Player: " << playerNames[playerState.playerNameIndex] << std::endl;
            std::cout << "Hand: "; playerState.playerHand.print(std::cout, 5);
            std::cout << "Rank: " << playerState.handRank << std::endl;
            std::cout << std::endl << std::endl;
        }

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

// Overload output stream operators for HoldEmHandRank
std::ostream &operator<<(std::ostream &os, const HoldEmHandRank &handRank){
    os << HoldEmGame::RankNames[static_cast<int>(handRank)];
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
    if (mySet.size() != boardMax) {
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
    bool isLowAce = mySet[0].myRank == HoldEmRank::five && mySet[boardMax - 1].myRank == HoldEmRank::ace;
    bool isHighAce = mySet[0].myRank == HoldEmRank::ace && mySet[1].myRank == HoldEmRank::king;
    if (isSameSuit && (isConsecutive || isLowAce || isHighAce)) {
        return HoldEmHandRank::straightflush;
    }

    // return fourofakind if four cards have the same rank
    for (size_t i = 0; i <= mySet.size() - boardMax + 1; ++i) {
        if (mySet[i].myRank == mySet[i + 1].myRank &&
            mySet[i].myRank == mySet[i + 2].myRank &&
            mySet[i].myRank == mySet[i + 3].myRank) {
            return HoldEmHandRank::fourofakind;
        }
    }

    // return fullhouse if three cards have the same rank and the other two cards have the same rank
    if ((mySet[0].myRank == mySet[1].myRank && mySet[1].myRank == mySet[2].myRank && mySet[boardMax - 2].myRank == mySet[boardMax - 1].myRank) ||
        (mySet[0].myRank == mySet[1].myRank && mySet[2].myRank == mySet[3].myRank && mySet[boardMax - 2].myRank == mySet[boardMax - 1].myRank)) {
        return HoldEmHandRank::fullhouse;
    }

    // return flush if all five cards are of the same suit
    if (std::all_of(mySet.begin(), mySet.end(), [&mySet](const auto &card) { return card.mySuit == mySet[0].mySuit; })) {
        return HoldEmHandRank::flush;
    }

    // return straight if the ranks of the cards are consecutive (with the special rule that A 2 3 4 5 and 10 J Q K A are the lowest and highest valid straights respectively, but any hand with cards ranked K A 2 is not considered a straight)
    bool isStraight = true;
    for (int i = 0; i < boardMax - 1; ++i) {
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
    if ((mySet[0].myRank == mySet[1].myRank && mySet[1].myRank == mySet[2].myRank && mySet[2].myRank != mySet[3].myRank && mySet[3].myRank != mySet[4].myRank) ||
        (mySet[1].myRank == mySet[2].myRank && mySet[2].myRank == mySet[3].myRank && mySet[1].myRank != mySet[0].myRank && mySet[3].myRank != mySet[4].myRank) ||
        (mySet[2].myRank == mySet[3].myRank && mySet[3].myRank == mySet[4].myRank && mySet[2].myRank != mySet[0].myRank && mySet[0].myRank != mySet[1].myRank)) {
        return HoldEmHandRank::threeofakind;
    }

    // return pair if only two cards in the hand have the same rank
    // return twopair if two cards have the same rank and two other cards share a different rank and the fifth card is of yet another rank
    size_t pairCount = 0;
    for (int i = 0; i < boardMax - 1; ++i) {
        if (mySet[i].myRank == mySet[i + 1].myRank) {
            ++pairCount;
            ++i;
        }
    }
    if (pairCount == 1) {
        return HoldEmHandRank::pair;
    }
    else if (pairCount == 2) {
        return HoldEmHandRank::twopair;
    }
    
    // otherwise it should return xhigh
    return HoldEmHandRank::xhigh;
}

// Constructor
HoldEmGame::PlayerState::PlayerState(CardSet<HoldEmRank, Suit> handSet, size_t playName, HoldEmHandRank holdRank) : playerHand(handSet), playerNameIndex(playName), handRank(holdRank) {}

/**
 * @brief Extracts a card combination of a given length from a hand
 *
 * @param hand The hand from which to extract the combination
 * @param length The length of the card combination to be checked
 * @return A tuple containing the starting index of the combination in the hand and the rank of the cards
 */
std::tuple<size_t, HoldEmRank> HoldEmGame::extractMultiFromSet(const std::vector< Card<HoldEmRank, Suit> >& hand, size_t length) {
    for (size_t index = 0; index <= hand.size() - length; ++index) {
        bool returnFlag = true;
        for (size_t i = 1; i < length; i++)
        {
            if (hand[index].myRank != hand[index + i].myRank)
            {
                returnFlag = false;
            }
        }

        if (returnFlag)
        {
            return std::make_tuple(index, hand[index].myRank);
        }

    }
}

/**
 * @brief Compares two hands based on certain poker rules to find which one is superior
 *
 * @param leftHand The hand of the first player
 * @param rightHand The hand of the second player
 * @param length The length of the card combination to be checked (e.g., 2 for a pair)
 * @param next The next hand rank to be used for comparison in case of a tie
 * @return Returns true if the left hand is superior, false otherwise
 */
bool HoldEmGame::compareMultiSet(CardSet<HoldEmRank, Suit> &leftHand, CardSet<HoldEmRank, Suit>& rightHand, size_t length, HoldEmHandRank next) {
    std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
    std::vector< Card<HoldEmRank, Suit> >* myLeftSet = &(leftHand.*setPtr);
    std::vector< Card<HoldEmRank, Suit> >* myRightSet = &(rightHand.*setPtr);
    HoldEmRank lrank, rrank;
    size_t lindex, rindex;
    std::tie(lindex, lrank) = extractMultiFromSet(*myLeftSet, length);
    std::tie(rindex, rrank) = extractMultiFromSet(*myRightSet, length);
    if (lrank < rrank) {
        return true;
    }
    else if (lrank > rrank) {
        return false;
    }
    else {
        myLeftSet->erase(myLeftSet->begin() + lindex, myLeftSet->begin() + lindex + length);
        myRightSet->erase(myRightSet->begin() + rindex, myRightSet->begin() + rindex + length);
        return HoldEmGame::PlayerState(leftHand, 0, next) < HoldEmGame::PlayerState(rightHand, 0, next);
    }
}

/**
 * @brief Overloads the '<' operator to compare two PlayerState objects in HoldEmGame
 *
 * @param lps The PlayerState object on the left
 * @param rps The PlayerState object on the right
 * @return true if the left-hand side PlayerState is considered "less than" the right
 */
bool operator<(const HoldEmGame::PlayerState& lps, const HoldEmGame::PlayerState& rps) {

    // The cases handset not equal
    if (lps.handRank < rps.handRank) {
        return true;
    }
    else if (lps.handRank > rps.handRank) {
        return false;
    }

    // The case when handRank is equal

    // Create a deep copy of player's handset
    CardSet<HoldEmRank, Suit> leftHandCopy(lps.playerHand);
    CardSet<HoldEmRank, Suit> rightHandCopy(rps.playerHand);

    std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
    std::vector< Card<HoldEmRank, Suit> >* myLeftSet = &(leftHandCopy.*setPtr);
    std::vector< Card<HoldEmRank, Suit> >* myRightSet = &(rightHandCopy.*setPtr);

    // Sort by rank and then suit (if needed)
    std::sort(myLeftSet->begin(), myLeftSet->end(), lessRank<HoldEmRank, Suit>);
    std::sort(myRightSet->begin(), myRightSet->end(), lessRank<HoldEmRank, Suit>);
    // vector in descending order
    std::reverse(myLeftSet->begin(), myLeftSet->end());
    std::reverse(myRightSet->begin(), myRightSet->end());

    // compare the two hands based on HoldEmHandRank
    switch (lps.handRank)
    {
    case HoldEmHandRank::xhigh:
    case HoldEmHandRank::flush: 
    {
        for (size_t i = 0; i < myLeftSet->size(); i++)
        {
            if ((*myLeftSet)[i].myRank < (*myRightSet)[i].myRank) {
                return true;
            }
            else if ((*myLeftSet)[i].myRank > (*myRightSet)[i].myRank) {
                return false;
            }
        }
        return false;
    }
        break;
    case HoldEmHandRank::pair:
        return HoldEmGame::compareMultiSet(leftHandCopy, rightHandCopy, 2, HoldEmHandRank::xhigh);
        break;
    case HoldEmHandRank::twopair:
        return HoldEmGame::compareMultiSet(leftHandCopy, rightHandCopy, 2, HoldEmHandRank::pair);
        break;
    case HoldEmHandRank::threeofakind:
        return HoldEmGame::compareMultiSet(leftHandCopy, rightHandCopy, 3, HoldEmHandRank::xhigh);
        break;
    case HoldEmHandRank::fullhouse:
        return HoldEmGame::compareMultiSet(leftHandCopy, rightHandCopy, 3, HoldEmHandRank::pair);
        break;
    case HoldEmHandRank::fourofakind:
        return HoldEmGame::compareMultiSet(leftHandCopy, rightHandCopy, 4, HoldEmHandRank::xhigh);
        break;
    case HoldEmHandRank::straight:
    case HoldEmHandRank::straightflush:
    {
        if ((*myLeftSet)[0].myRank < (*myRightSet)[0].myRank) {
            return true;
        }
        else {
            return false;
        }
        break;
    }
    default:
        break;
    }
}
