#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include "tetristype.h"
#include "../IO/gameboyIO.h"
#include <string>

using std::string;


class TetrisBoard {

public:
    TetrisBoard();
    int** getGameBoard();
    void moveBlock(int direction);
    void downBlock();
    void eraseAllLine();

private:
    void initBoard();
    void getNextBlock();
    void placeBlock(int offsetX, int offsetY, int kind, int rotation);
    void filledBlock(int offsetX, int offsetY);
    void clearBlock(int offsetX, int offsetY);
    bool isPossibleMove();
    void eraseLine(int rowNo);


    int blockKind, blockRotation;
    int offsetX, offsetY;
    int nextBlockKind, nextBlockRotation;
    int nextOffsetX, nextOffsetY;
    int gameBoard[MAIN_GAME_BOARD_HEIGHT + 5][MAIN_GAME_BOARD_WIDTH + 5];
    bool isFilled[MAIN_GAME_BOARD_HEIGHT + 5][MAIN_GAME_BOARD_WIDTH + 5];
    TetrisType tetrisBlock;

};

#endif