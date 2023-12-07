/**
 * File: lab3.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: contain the main function, test whether the game goes correctly.
 */
#include <iostream>
#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "UnoDeck.h"
#include "Game.h"
#include <memory>
#include <cstring>
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include "GoFishGame_T.h"


const int SUCCESS = 0;
const int INVALIDINPUT = 1;
const int INVALIDPLAYERNUM = 2;
const int INVALIDGAMENAME = 3;
const int INVALIDPTR = 4;
const int OTHERERROR = 5;


const char** create_new_argv(const char* argv[], int& argc) {
    // Allocate new_argv with one less argument
    int new_argc = argc - 1; // Update the new_argc
    const char** new_argv = new const char* [new_argc + 1]; // +1 for the null terminator

    // opy the arguments except the third one
    for (int i = 0, j = 0; i < argc; i++) {
        if (i == 2) continue; // Skip the third argument

        new_argv[j] = argv[i]; // Copy the pointer
        j++;
    }

    new_argv[new_argc] = NULL; // Null terminate the new_argv array
    return new_argv;
}

// Function to create a game based on command line arguments
std::shared_ptr<Game> create(int argc, const char* argv[]) {
    std::shared_ptr<Game> myGamePtr;
    const char** new_argv = nullptr;
    if (strcmp(argv[1], "Pinochle") == 0) {
        myGamePtr = std::make_shared<PinochleGame>(argc, argv);
    }
    else if (strcmp(argv[1], "HoldEm") == 0) {
        myGamePtr = std::make_shared<HoldEmGame>(argc, argv);
    }
    else if (strcmp(argv[1], "GoFish") == 0) {
        try {
            new_argv = create_new_argv(argv, argc);
            if (strcmp(argv[2], "HoldEm") == 0)
            {
                myGamePtr = std::make_shared<GoFishGame<Suit, HoldEmRank, HoldEmDeck>>(argc, new_argv);
            }
            else if (strcmp(argv[2], "Pinochle") == 0)
            {
                myGamePtr = std::make_shared<GoFishGame<Suit, PinochleRank, PinochleDeck>>(argc, new_argv);
            }
            else if (strcmp(argv[2], "Uno") == 0)
            {
                myGamePtr = std::make_shared<GoFishGame<Color, UnoRank, UnoDeck>>(argc, new_argv);
            }
            else {
                throw std::invalid_argument("Must provide valid Deck for GoFish: HoldEm, Pinochle or Uno");
            }
            delete[] new_argv;
            new_argv = nullptr;
        }
        catch (const std::exception& e)
        {
            if (new_argv != nullptr)
            {
                delete[] new_argv;
                new_argv = nullptr;
            }
            throw e;
        }
    }
    return myGamePtr;
}

// Function to display correct usage of the program
void usage(std::ostream& os) {
    os << "Usage: lab3 <Game> [<Deck>] <Players>" << std::endl;
    os << "Game should be either Pinochle, HoldEm, or GoFish." << std::endl;
    os << "Pinochle needs 4 players." << std::endl;
    os << "HoldEm needs 2-9 players." << std::endl;
    os << "GoFish needs 2-5 players." << std::endl;
}

int main(int argc, const char* argv[]) {
    // Check for minimum number of arguments
    if (argc < 2)
    {
        usage(std::cout);
        return INVALIDINPUT;
    }
    // Check for Pinochle game-specific conditions
    else if (strcmp(argv[1], "Pinochle") == 0) {
        if (argc != 6) {
            usage(std::cout);
            return INVALIDPLAYERNUM;
        }
    }
    // Check for HoldEm game-specific conditions
    else if (strcmp(argv[1], "HoldEm") == 0) {
        if (argc < 4 || argc > 11) {
            usage(std::cout);
            return INVALIDPLAYERNUM;
        }
    }
    // Check for GoFish game-specific conditions
    else if (strcmp(argv[1], "GoFish") == 0) {
        if (argc < 5 || argc > 8) {
            usage(std::cout);
            return INVALIDPLAYERNUM;
        }
    }
    // Game other than Pinochle or HoldEm or GoFish
    else
    {
        usage(std::cout);
        return INVALIDGAMENAME;
    }

    try
    {
        // Create the game based on command line arguments
        std::shared_ptr<Game> myGame = create(argc, argv);
        if (myGame)
        {
            myGame->play();
        }
        else
        {
            std::cout << "Error: Invalid ptr";
            return INVALIDPTR;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return OTHERERROR;
    }

    return SUCCESS;
}
