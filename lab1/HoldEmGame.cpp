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
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

/**
 * @brief Prints the cards held by each player
 *
 * @param os The output stream to the player's cards be printed
 * @param length The number of cards per line when printing
 */
void HoldEmGame::printPlayersCards(std::ostream& os, size_t length)
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
