/**
 * File: Game.cpp
 * Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
 * Purpose: Implementation of the class: Game.
 */

#include "Game.h"
#include <iostream>

/**
 * @brief Constructor for the Game class
 *
 * @param argc The number of command-line arguments
 * @param argv Array to contain the command-line arguments
 */
Game::Game(int argc, const char *argv[]) {
    //Choose solution 2: start at position 2, so that argc and argv can be directly transmitted.
    for (int i = 2; i < argc; ++i) {
        playerNames.push_back(std::string(argv[i]));
    }
}

/**
 * @brief Asks the user whether they want to end the game
 *
 * @param is Input stream to read the user's response
 * @param os Output stream to display the question
 * @return True if the user wants to end
 */
bool Game::askEnd(std::istream &is, std::ostream &os)
{
    os << "Do you want to end the game? (type yes to end): " << std::endl;
    std::string response;
    is >> response;

    return response == "yes";
}
