//
// Created by Wenzel Luis on 9/28/23.
//

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Game {
protected:
    std::vector<std::string> playerNames;

public:
    Game(int argc, const char *argv[]);

    virtual int play() = 0;
};

#endif // GAME_H

