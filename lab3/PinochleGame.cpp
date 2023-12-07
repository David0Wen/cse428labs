/**
* File: PinochleGame.cpp
* Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
* Purpose: Implementation of PinochleGame class and functions.
*/
#include "PinochleGame.h"

const int SUCCESS = 0;

// num of cards displayed per line when printing a player's hand
const int rowLength = 6;
// Operate 3 cards each time
const int packetSize = 3;

const int allSuitsNum = 8;

// Static list, assigning all possible melds(enum) with different names
const char* PinochleGame::MeldNames[] = {
    "dix", "offsuitmarriage", "fortyjacks", "pinochle", "insuitmarriage",
    "sixtyqueens", "eightykings", "hundredaces", "insuitrun", "doublepinochle",
    "fourhundredjacks", "sixhundredqueens", "eighthundredkings", "thousandaces", "insuitdoublerun"
};

// Static list, assigning all possible melds(enum) with different points
const unsigned int PinochleGame::MeldPoints[] = {
    10,   // dix
    20,   // offsuitmarriage
    40,   // fortyjacks
    40,   // pinochle
    40,   // insuitmarriage
    60,   // sixtyqueens
    80,   // eightykings
    100,  // hundredaces
    150,  // insuitrun
    300,  // doublepinochle
    400,  // fourhundredjacks
    600,  // sixhundredqueens
    800,  // eighthundredkings
    1000, // thousandaces
    1500  // insuitdoublerun
};

/**
 * @brief Constructor for the PinochleGame class
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 */
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv)
{
    // Calculate the number of players based on argc
    int numPlayers = argc - 2; // Subtract 2 for program name and game name

    // Initialize the hands vector with empty hands for each player
    playerHands.resize(numPlayers);
}

/**
 * @brief Deal cards to each player
 */
void PinochleGame::deal()
{
    try 
    {
        // Iterate through each player's hand and deal cards in packets
        for (auto iter = playerHands.begin(); !myDeck.is_empty(); ++iter)
        {
            if (iter == playerHands.end())
            {
                iter = playerHands.begin();
            }
            // Deal 'packetSize' cards to the current player's hand
            for (int i = 0; i < packetSize; ++i) {
                myDeck >> *iter;
            }
        }
    }
    catch (const std::runtime_error &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

/**
 * @brief Print the cards held by each player
 *
 * @param os Output stream to which the player names and cards are printed
 * @param length Number of cards to print per line
 */
void PinochleGame::printPlayersCards(std::ostream &os, size_t length)
{
    auto handIter = playerHands.begin();
    auto nameIter = playerNames.begin();
    // Iterate through all players
    while (nameIter != playerNames.end())
    {
        // Print player name
        os << "Name: " << *nameIter << std::endl;
        // Print the cards in the current player's hand
        (*handIter).print(os, length);
        // Lab2: Print possible melds
        std::vector<PinochleMelds> melds;
        suit_independent_evaluation(*handIter, melds);

        if (melds.empty()) {
        std::cout << "No possible melds!" << std::endl;
        }
        else {
            os << "Possible melds:" << std::endl;
            for (auto &meld : melds) {
                os << meld << std::endl; // Using the shift operator to print meld label and value
            }
        }
        os << std::endl;

        ++handIter;
        ++nameIter;
    }
}

/**
 * @brief Collect the cards from each player's hand back into the deck
 */
void PinochleGame::roundCollect()
{
    // Iterate through each player's hand to collect cards back into the deck
    for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
    {
        myDeck.collect(*iter);
    }
}

/**
 * @brief Main gameplay loop for Pinochle
 *
 * @return An integer representing the status of the function
 */
int PinochleGame::play()
{
    std::cout << "Welcome to Pinochle!" << std::endl;

    while (true)
    {
        // (1) call the deck's shuffle member function;
        myDeck.shuffle();
        // (2) call the deal member function to distribute the cards to the players;
        deal();
        // (3) print out each player's name and then the cards in their hand to the standard output stream;
        printPlayersCards(std::cout, rowLength);
        // (4) use the deck's collect member function repeatedly to move the cards back out of each player's hand into the deck;
        roundCollect();
        // (5) (6)
        if (askEnd(std::cin, std::cout)) {
            std::cout << "Thanks for playing Pinochle!" << std::endl;
            return SUCCESS;
        }
        std::cout << "Starting a new round..." << std::endl;
    }
}

/**
* Output the melds feature to std::ostream
* @param os the stream you want to output to
* @param meld the object you want to output
* @return the reference of the input stream
*/
std::ostream &operator<<(std::ostream &os, const PinochleMelds &meld)
{
    os << PinochleGame::MeldNames[static_cast<int>(meld)] << " " << PinochleGame::MeldPoints[static_cast<int>(meld)];
    return os;
}

/**
* @brief Checks if the vector of Cards(between start and end) has four different suit for given rank
* @param beg The start iterator of the given interval
* @param end The end iterator of the given interval
* @return True if have four different suit
*/
bool PinochleGame::isFourSuits(const std::vector<Card<PinochleRank, Suit>>::iterator &beg, const std::vector<Card<PinochleRank, Suit>>::iterator &end, PinochleRank myRank)
{
    bool hasClubs = std::any_of(beg, end, [=](const Card<PinochleRank, Suit> &obj) {
        return obj.myRank == myRank && obj.mySuit == Suit::clubs;
        });
    bool hasDiamonds = std::any_of(beg, end, [=](const Card<PinochleRank, Suit> &obj) {
        return obj.myRank == myRank && obj.mySuit == Suit::diamonds;
        });
    bool hasHearts = std::any_of(beg, end, [=](const Card<PinochleRank, Suit> &obj) {
        return obj.myRank == myRank && obj.mySuit == Suit::hearts;
        });
    bool hasSpades = std::any_of(beg, end, [=](const Card<PinochleRank, Suit> &obj) {
        return obj.myRank == myRank && obj.mySuit == Suit::spades;
        });

    return hasClubs && hasDiamonds && hasHearts && hasSpades;
}

/**
* @brief Checks if the CardSet has several different possible melds, insert all possible melds into the given vector
* @param playerHand The CardSet to eval
* @param melds the given vector reference to insert all possible melds
*/
void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit> &playerHand, std::vector<PinochleMelds> &melds)
{
    CardSet<PinochleRank, Suit> handCopy(playerHand);
    // Sort by rank and then suit (if needed)
    handCopy.sort();

//    std::vector< Card<PinochleRank, Suit> > CardSet<PinochleRank, Suit>::* setPtr = CardSet<PinochleRank, Suit>::getSetPtr();
//    std::vector< Card<PinochleRank, Suit> > mySet = handCopy.*setPtr;
    std::vector< Card<PinochleRank, Suit> > mySet(handCopy.begin(), handCopy.end());

//    // Sort by rank and then suit (if needed)
//    std::sort(mySet.begin(), mySet.end(), lessRank<PinochleRank, Suit>);
    // vector in decending order
    std::reverse(mySet.begin(), mySet.end());

    /*
    thousandaces for all 8 aces (A♠ A♠ A♥ A♥ A♦ A♦ A♣ A♣)
    hundredaces for an ace of each suit (A♠ A♥ A♦ A♣) but not if the hand has thousandaces
    eighthundredkings for all 8 kings (K♠ K♠ K♥ K♥ K♦ K♦ K♣ K♣)
    eightykings for a king of each suit (K♠ K♥ K♦ K♣) but not if the hand has eighthundredkings
    sixhundredqueens for all 8 queens (Q♠ Q♠ Q♥ Q♥ Q♦ Q♦ Q♣ Q♣)
    sixtyqueens for a queen of each suit (Q♠ Q♥ Q♦ Q♣) but not if the hand has sixhundredqueens
    fourhundredjacks for all 8 jacks (J♠ J♠ J♥ J♥ J♦ J♦ J♣ J♣)
    fortyjacks for a jack of each suit (J♠ J♥ J♦ J♣) but not if the hand has fourhundredjacks
    doublepinochle for two jacks of diamonds and two queens of spades (J♦ J♦ Q♠ Q♠)
    pinochle for a jack of diamonds and a queen of spades (J♦ Q♠) but not if the hand has doublepinochle
    */
    if (std::count_if(mySet.begin(), mySet.end(), 
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::ace; }) == allSuitsNum) {
        melds.push_back(PinochleMelds::thousandaces);
    }
    else if (std::count_if(mySet.begin(), mySet.end(), 
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::ace; }) >= allSuitsNum/2) {
        if (isFourSuits(mySet.begin(), mySet.end(), PinochleRank::ace)) {
            melds.push_back(PinochleMelds::hundredaces);
        }
    }
    if (std::count_if(mySet.begin(), mySet.end(), 
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::king; }) == allSuitsNum) {
        melds.push_back(PinochleMelds::eighthundredkings);
    }
    else if (std::count_if(mySet.begin(), mySet.end(), 
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::king; }) >= allSuitsNum/2) {
        if (isFourSuits(mySet.begin(), mySet.end(), PinochleRank::king)) {
            melds.push_back(PinochleMelds::eightykings);
        }
    }
    if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::queen; }) == allSuitsNum) {
        melds.push_back(PinochleMelds::sixhundredqueens);
    }
    else if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::queen; }) >= allSuitsNum/2) {
        if (isFourSuits(mySet.begin(), mySet.end(), PinochleRank::queen)) {
            melds.push_back(PinochleMelds::sixtyqueens);
        }
    }
    if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::jack; }) == allSuitsNum) {
        melds.push_back(PinochleMelds::fourhundredjacks);
    }
    else if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::jack; }) >= allSuitsNum/2) {
        if (isFourSuits(mySet.begin(), mySet.end(), PinochleRank::jack)) {
            melds.push_back(PinochleMelds::fortyjacks);
        }
    }
    if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::jack && obj.mySuit == Suit::diamonds; }) == 2) {
        if (std::count_if(mySet.begin(), mySet.end(),
            [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::queen && obj.mySuit == Suit::spades; }) == 2) {
            melds.push_back(PinochleMelds::doublepinochle);
        }
        else if (std::count_if(mySet.begin(), mySet.end(),
            [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::queen && obj.mySuit == Suit::spades; }) == 1) {
            melds.push_back(PinochleMelds::pinochle);
        }
    }
    else if (std::count_if(mySet.begin(), mySet.end(),
        [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::jack && obj.mySuit == Suit::diamonds; }) == 1) {
        if (std::count_if(mySet.begin(), mySet.end(),
            [](const Card<PinochleRank, Suit> &obj) {return obj.myRank == PinochleRank::queen && obj.mySuit == Suit::spades; }) >= 1) {
            melds.push_back(PinochleMelds::pinochle);
        }
    }
}
