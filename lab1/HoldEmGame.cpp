/*
// File: HoldEmGame.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu
*/
#include "HoldEmGame.h"

const int SUCCESS = 0;

const int playerCards = 2;
const int boardMax = 5;

HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), myState(HoldEmState::preflop)
{
    // Calculate the number of players based on argc
    int numPlayers = argc - 2; // Subtract 2 for program name and game name

    // Initialize the hands vector with empty hands for each player
    playerHands.resize(numPlayers);
}

void HoldEmGame::deal()
{
    try
    {
        switch (myState)
        {
        case HoldEmState::preflop:
            for (int i = 0; i < playerCards; ++i)
            {
                for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
                {
                    myDeck >> *iter;
                }
            }
            myState = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            for (int i = 0; i < 3; ++i)
            {
                myDeck >> commonBoard;
            }
            myState = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            myDeck >> commonBoard;
            myState = HoldEmState::river;
            break;
        case HoldEmState::river:
            myDeck >> commonBoard;
            myState = HoldEmState::undefined;
            break;
        default:
            break;
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

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

void HoldEmGame::roundCollect()
{
    for (auto iter = playerHands.begin(); iter != playerHands.end(); ++iter)
    {
        myDeck.collect(*iter);
    }
    myDeck.collect(commonBoard);
}

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
