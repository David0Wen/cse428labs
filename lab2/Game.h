/**
// File: Game.h
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Declaration of base class Game.
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

// Abstract base class for card game
class Game {
protected:
    // Store the names of the players
    std::vector<std::string> playerNames;

public:
    // Constructor: initialize the player names
    Game(int argc, const char *argv[]);

    // Pure virtual function for playing the game
    virtual int play() = 0;
    // Prompts the user to and captures the response
    bool askEnd(std::istream &, std::ostream &);
};

#endif // GAME_H

