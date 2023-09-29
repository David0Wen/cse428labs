//
// Created by Wenzel Luis on 9/28/23.
//

#include "Game.h"

Game::Game(int argc, const char *argv[]) {
    //选择方案（1）或（2）来确定从哪里开始迭代
    //方案（1）：从位置2开始，跳过 argv[0]（可执行文件名）和 argv[1]（游戏名）
    for (int i = 2; i < argc; ++i) {
        playerNames.push_back(std::string(argv[i]));
    }

    //方案（2），则从位置 0 开始迭代
//    for (int i = 0; i < argc; ++i) {
//        playerNames.push_back(std::string(argv[i]));
//    }
}
