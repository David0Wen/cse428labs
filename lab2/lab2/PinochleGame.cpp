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
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

/**
 * @brief Print the cards held by each player
 *
 * @param os Output stream to which the player names and cards are printed
 * @param length Number of cards to print per line
 */
void PinochleGame::printPlayersCards(std::ostream& os, size_t length)
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
