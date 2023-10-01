/*
// File: PinochleGame.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu
*/
#include "PinochleGame.h"

const int SUCCESS = 0;

const int rowLength = 6;
const int packetSize = 3;

PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv)
{
    // Calculate the number of players based on argc
    int numPlayers = argc - 2; // Subtract 2 for program name and game name

    // Initialize the hands vector with empty hands for each player
    playerHands.resize(numPlayers);
}

void PinochleGame::deal()
{
    try 
    {
        for (auto iter = playerHands.begin(); !myDeck.is_empty(); ++iter)
        {
            if (iter == playerHands.end())
            {
                iter = playerHands.begin();
            }
            for (int i = 0; i < packetSize; ++i) {
                myDeck >> *iter;
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

void PinochleGame::printPlayersCards(std::ostream& os, size_t length)
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

void PinochleGame::roundCollect()
{
    for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
    {
        myDeck.collect(*iter);
    }
}

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
