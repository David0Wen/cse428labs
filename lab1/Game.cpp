/*
// File: Game.cpp
// Created by Wenzel Luis on 9/28/23.
*/

#include "Game.h"
#include <iostream>

Game::Game(int argc, const char *argv[]) {
    //Choose solution 2: start at position 2, so that argc and argv can be directly transmitted.
    for (int i = 2; i < argc; ++i) {
        playerNames.push_back(std::string(argv[i]));
    }

}

bool Game::askEnd(std::istream& is, std::ostream& os)
{
    os << "Do you want to end the game? (type yes to end): " << std::endl;
    std::string response;
    is >> response;

    return response == "yes";
}
