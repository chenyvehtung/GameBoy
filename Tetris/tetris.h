#ifndef TETRIS_H_
#define TETRIS_H_

#include "tetrisboard.h"
#include "../IO/gameboyIO.h"

class Tetris {
public:
    void startGame();    
private:
    TetrisBoard tetrisBoard;
};

#endif