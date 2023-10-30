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

        // 5.1 declare a vector of the nested struct type PlayerState
        std::vector<PlayerState> playerHandInfos;
        // 5.2 initialize the vector with each player's information to playerHandInfos
        for (size_t i = 0; i < playerHands.size(); ++i) {
            PlayerState info(playerHands[i], playerNames[i], HoldEmHandRank::undefined);
            playerHandInfos.push_back(info);
        }

        // Iterate through the vector to perform hand evaluation
        CardSet<HoldEmRank, Suit> combinedHand;
        std::vector< Card<HoldEmRank, Suit> >* combinedSetPtr = &(combinedHand.*CardSet<HoldEmRank, Suit>::getSetPtr());
        for (auto &playerState : playerHandInfos)
        {
            // Combine the player's hand with the common board
            std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();

            std::vector< Card<HoldEmRank, Suit> > playerSet = playerState.playerHand.*setPtr;
            std::vector< Card<HoldEmRank, Suit> > boardSet = commonBoard.*setPtr;

            // Combine the player's hand with the common board
            playerSet.insert(playerSet.end(), boardSet.begin(), boardSet.end());

            // Now playerSet contains the combined hand.
            // create a new CardSet from this to represent
            *combinedSetPtr = playerSet;
//            combinedHand.myCardSet = playerSet;

            // Evaluate the hand using hand evaluation function
//            HoldEmHandRank rank = holdem_hand_evaluation(combinedHand);
            HoldEmHandRank rank = holdem_hand_evaluation(playerState.playerHand);

            // Update the player's hand rank
            playerState.handRank = rank;
        }

        // Sort the playerStates vector based on hand rank
        std::sort(playerHandInfos.begin(), playerHandInfos.end(), [](const PlayerState &a, const PlayerState &b)
        {
            return a.handRank > b.handRank;
        });

        // Print sorted player details
        for (auto &playerState : playerHandInfos)
        {
            std::cout << "Player: " << playerState.playerName << std::endl;
            std::cout << "Hand: ";
            combinedHand.print(std::cout, combinedSetPtr->size());
            std::cout << "Rank: " << playerState.handRank << std::endl;
        }

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

// get pair information
void extractPairInfo(const std::vector< Card<HoldEmRank, Suit> > &hand, HoldEmRank &pairRank, std::vector<HoldEmRank> &nonPairRanks) {
    const int N = static_cast<int>(HoldEmRank::ace);
    std::vector<int> rankCount(N + 1, 0);

    // Count the occurrences of each rank
    for (const auto &card : hand) {
        if (card.myRank != HoldEmRank::undefined) {
            rankCount[static_cast<int>(card.myRank)]++;
        }
    }

    // Identify the pair and the non-pair cards
    for (int i = 0; i <= N; ++i) {
        int count = rankCount[i];
        if (count == 2) {
            pairRank = static_cast<HoldEmRank>(i);
        } else {
            for (int j = 0; j < count; ++j) {
                nonPairRanks.push_back(static_cast<HoldEmRank>(i));
            }
        }
    }

    // Sort the non-pair ranks in descending order for later comparison
    std::sort(nonPairRanks.begin(), nonPairRanks.end(), std::greater<HoldEmRank>());
}

// get twopair information
void extractTwoPairInfo(const std::vector< Card<HoldEmRank, Suit> > &hand, HoldEmRank &higherPair, HoldEmRank &lowerPair, HoldEmRank &fifthCard) {
    if (hand[0].myRank == hand[1].myRank && hand[2].myRank == hand[3].myRank) {
        higherPair = hand[2].myRank;
        lowerPair = hand[0].myRank;
        fifthCard = hand[4].myRank;
    } else if (hand[1].myRank == hand[2].myRank && hand[3].myRank == hand[4].myRank) {
        higherPair = hand[3].myRank;
        lowerPair = hand[1].myRank;
        fifthCard = hand[0].myRank;
    } else {
        higherPair = hand[1].myRank;
        lowerPair = hand[3].myRank;
        fifthCard = hand[4].myRank;
    }
}

// get rank of threeofakind
void extractThreeOfAKindRank(const std::vector< Card<HoldEmRank, Suit> > &hand, HoldEmRank &threeOfAKindRank) {
    // 假设hand已经排序
    for (size_t i = 0; i <= hand.size() - 3; ++i) {
        if (hand[i].myRank == hand[i+1].myRank && hand[i+1].myRank == hand[i+2].myRank) {
            threeOfAKindRank = hand[i].myRank;
            return;
        }
    }
}

// get fullhouse information
void extractFullHouseInfo(const std::vector< Card<HoldEmRank, Suit> > &hand, HoldEmRank &threeOfAKindRank, HoldEmRank &pairRank) {
    const int N = static_cast<int>(HoldEmRank::ace);
    std::vector<int> rankCount(N + 1, 0);

    // Count the occurrences of each rank
    for (const auto &card : hand) {
        if (card.myRank != HoldEmRank::undefined) {
            rankCount[static_cast<int>(card.myRank)]++;
        }
    }

    // Identify the three-of-a-kind and the pair
    for (int i = 0; i <= N; ++i) {
        int count = rankCount[i];
        if (count == 3) {
            threeOfAKindRank = static_cast<HoldEmRank>(i);
        } else if (count == 2) {
            pairRank = static_cast<HoldEmRank>(i);
        }
    }
}

// Extract four of a kind rank
void extractFourOfAKindRank(const std::vector< Card<HoldEmRank, Suit> > &hand, HoldEmRank &fourOfAKindRank, HoldEmRank &fifthCard) {
    const int N = static_cast<int>(HoldEmRank::ace);
    std::vector<int> rankCount(N + 1, 0);

    // Count the occurrences of each rank
    for (const auto &card : hand) {
        if (card.myRank != HoldEmRank::undefined) {
            rankCount[static_cast<int>(card.myRank)]++;
        }
    }

    // Identify the four of a kind and the fifth card
    for (int i = 0; i <= N; ++i) {
        int count = rankCount[i];
        if (count == 4) {
            fourOfAKindRank = static_cast<HoldEmRank>(i);
        } else if (count == 1) {
            fifthCard = static_cast<HoldEmRank>(i);
        }
    }
}


// Compare PlayerState
bool operator<(const HoldEmGame::PlayerState &lps, const HoldEmGame::PlayerState &rps) {

    // The cases handset not equal
    if (lps.handRank < rps.handRank) {
        return true;
    }
    if (lps.handRank > rps.handRank) {
        return false;
    }

    // The case when handRank is equal

    // Create a deep copy of player's handset
    CardSet<HoldEmRank, Suit> leftHandCopy(lps.playerHand);
    CardSet<HoldEmRank, Suit> rightHandCopy(rps.playerHand);

    std::vector< Card<HoldEmRank, Suit> > CardSet<HoldEmRank, Suit>::* setPtr = CardSet<HoldEmRank, Suit>::getSetPtr();
    std::vector< Card<HoldEmRank, Suit> > myLeftSet = leftHandCopy.*setPtr;
    std::vector< Card<HoldEmRank, Suit> > myRightSet = rightHandCopy.*setPtr;

    // Sort by rank and then suit (if needed)
    std::sort(myLeftSet.begin(), myLeftSet.end(), lessRank<HoldEmRank, Suit>);
    std::sort(myRightSet.begin(), myRightSet.end(), lessRank<HoldEmRank, Suit>);
    // vector in descending order
    std::reverse(myLeftSet.begin(), myLeftSet.end());
    std::reverse(myRightSet.begin(), myRightSet.end());

    // If both are pair
    if (lps.handRank == HoldEmHandRank::pair) {
        HoldEmRank leftPairRank, rightPairRank;
        std::vector<HoldEmRank> leftNonPairRanks, rightNonPairRanks;

        // Extract pair and non-pair information from both hands
        extractPairInfo(myLeftSet, leftPairRank, leftNonPairRanks);
        extractPairInfo(myRightSet, rightPairRank, rightNonPairRanks);

        // Compare pair ranks
        if (leftPairRank < rightPairRank) return true;
        if (leftPairRank > rightPairRank) return false;

        // Compare non-pair ranks
        for (size_t i = 0; i < leftNonPairRanks.size(); ++i) {
            if (leftNonPairRanks[i] < rightNonPairRanks[i]) return true;
            if (leftNonPairRanks[i] > rightNonPairRanks[i]) return false;
        }

        // If reach this point, the hands are equal
        return false;
    }

    // If both are twopair
    if (lps.handRank == HoldEmHandRank::twopair) {
        HoldEmRank leftHigherPair, leftLowerPair, leftFifthCard;
        HoldEmRank rightHigherPair, rightLowerPair, rightFifthCard;

        // Extract two pairs and a single from the left
        extractTwoPairInfo(myLeftSet, leftHigherPair, leftLowerPair, leftFifthCard);

        // Extract two pairs and a single from the right
        extractTwoPairInfo(myRightSet, rightHigherPair, rightLowerPair, rightFifthCard);

        // Compare two pair
        if (leftHigherPair < rightHigherPair) return true;
        if (leftHigherPair > rightHigherPair) return false;

        if (leftLowerPair < rightLowerPair) return true;
        if (leftLowerPair > rightLowerPair) return false;

        if (leftFifthCard < rightFifthCard) return true;
        if (leftFifthCard > rightFifthCard) return false;

        return false;
    }

    // If both are threeofakind
    if (lps.handRank == HoldEmHandRank::threeofakind) {
        HoldEmRank leftThreeOfAKindRank, rightThreeOfAKindRank;

        // Extract lefthand's three's rank
        extractThreeOfAKindRank(myLeftSet, leftThreeOfAKindRank);

        // Extract tighthand's three's rank
        extractThreeOfAKindRank(myRightSet, rightThreeOfAKindRank);

        if (leftThreeOfAKindRank < rightThreeOfAKindRank) {
            return true;
        }
        return false;
    }

    // If both are straight
    if (lps.handRank == HoldEmHandRank::straight) {
        HoldEmRank leftHighestCard = myLeftSet[0].myRank;
        HoldEmRank rightHighestCard = myRightSet[0].myRank;

        if (leftHighestCard < rightHighestCard) {
            return true;
        }
        return false;
    }

    // If both are flush or xhigh
    if (lps.handRank == HoldEmHandRank::flush || lps.handRank == HoldEmHandRank::xhigh) {
        for (size_t i = 0; i < myLeftSet.size(); ++i) {
            HoldEmRank leftRank = myLeftSet[i].myRank;
            HoldEmRank rightRank = myRightSet[i].myRank;

            if (leftRank < rightRank) {
                return true;
            }
            if (leftRank > rightRank) {
                return false;
            }
        }
        // If reach this point, the hands are equal
        return false;
    }

    // If both are fullhouse
    if (lps.handRank == HoldEmHandRank::fullhouse) {
        HoldEmRank leftThreeOfAKindRank, leftPairRank;
        HoldEmRank rightThreeOfAKindRank, rightPairRank;

        // Extract fullhouse information for both hands
        extractFullHouseInfo(myLeftSet, leftThreeOfAKindRank, leftPairRank);
        extractFullHouseInfo(myRightSet, rightThreeOfAKindRank, rightPairRank);

        // Compare three-of-a-kind ranks
        if (leftThreeOfAKindRank < rightThreeOfAKindRank) return true;
        if (leftThreeOfAKindRank > rightThreeOfAKindRank) return false;

        // Compare pair ranks
        if (leftPairRank < rightPairRank) return true;
        if (leftPairRank > rightPairRank) return false;

        return false;  // equal
    }

    // If both are fourofakind
    if (lps.handRank == HoldEmHandRank::fourofakind) {
        HoldEmRank leftFourOfAKindRank, leftFifthCard;
        HoldEmRank rightFourOfAKindRank, rightFifthCard;

        // Extract four of a kind information for both hands
        extractFourOfAKindRank(myLeftSet, leftFourOfAKindRank, leftFifthCard);
        extractFourOfAKindRank(myRightSet, rightFourOfAKindRank, rightFifthCard);

        // Compare four of a kind ranks
        if (leftFourOfAKindRank < rightFourOfAKindRank) return true;
        if (leftFourOfAKindRank > rightFourOfAKindRank) return false;

        // Compare fifth card if four of a kind ranks are equal
        if (leftFifthCard < rightFifthCard) return true;

        return false;  // If reach this point, the hands are equal
    }

    // If both are straightflush
    if (lps.handRank == HoldEmHandRank::straightflush) {
        HoldEmRank leftHighestCard = myLeftSet[0].myRank;
        HoldEmRank rightHighestCard = myRightSet[0].myRank;

        if (leftHighestCard < rightHighestCard) {
            return true;
        }
        return false;
    }

    return false;
}
