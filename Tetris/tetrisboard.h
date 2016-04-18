#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_
#include "../IO/gameboyboard.h"
#include "tetristype.h"

class TetrisBoard: public GameBoyBoard {
public:
    TetrisBoard();
    TetrisBoard(int score);

private:
    int blockKind, blockRotation;
    int nextBlockKind, nextBlockRotation;
    int blockX, blockY;
    TetrisType tetrisBlock;

    void initBoard(int score);
    void placeBlock(int winNum, int offsetY, int offsetX, int kind, int rotation);

};

#endif