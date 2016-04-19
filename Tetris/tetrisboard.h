#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_
#include "../IO/gameboyboard.h"
#include "tetristype.h"

class TetrisBoard: public GameBoyBoard {
public:
    TetrisBoard();
    TetrisBoard(int score);
    void moveBlock(int direction);

private:
    
    int nextBlockKind, nextBlockRotation;
    int blockX, blockY;
    int blockKind, blockRotation;
    TetrisType tetrisBlock;

    void initBoard(int score);
    void placeBlock(int winNum, int offsetY, int offsetX, int kind, int rotation);
    void filledBlock();
    void clearBlock();
    bool isPossibleMove(int offsetY, int offsetX, int rotation);
    void eraseLine(int rowNum);
    void eraseAllLine();
    void getNextBlock();

};

#endif