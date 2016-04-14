#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include "tetristype.h"
#include <map>
#include <string>
using std::map;
using std::string;

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 40

class TetrisBoard {

public:
    TetrisBoard();
    int** getGameBoard();
    map<string, int> getDisplayArg();
    void moveBlock(int direction);
    void downBlock();
    void eraseAllLine();

    enum {
        LEFT = 68,
        RIGHT = 67,
        DOWN = 66,
        UP = 65
    };

private:
    void initBoard();
    void getNextBlock();
    void placeBlock(int offsetX, int offsetY, int kind, int rotation);
    void filledBlock(int offsetX, int offsetY);
    void clearBlock(int offsetX, int offsetY);
    bool isPossibleMove();
    void eraseLine(int rowNo);
    void setDisplayArg() {
        DISPLAY_ARG["BOARD_WIDTH"] = BOARD_WIDTH;
        DISPLAY_ARG["BOARD_HEIGHT"] = BOARD_HEIGHT;
        DISPLAY_ARG["GAME_WIDTH"] = 15;
        DISPLAY_ARG["GAME_MARGIN"] = 5;
        DISPLAY_ARG["BOARD_WALL"] = 5;
        DISPLAY_ARG["BOARD_SPACE"] = 0;
        DISPLAY_ARG["BLOCK_SIMPLE"] = 2;
        DISPLAY_ARG["BLOCK_PIVOT"] = 1;
    };

    int blockKind, blockRotation;
    int offsetX, offsetY;
    int nextBlockKind, nextBlockRotation;
    int nextOffsetX, nextOffsetY;
    int gameBoard[BOARD_HEIGHT + 5][BOARD_WIDTH];
    bool isFilled[BOARD_HEIGHT + 5][BOARD_WIDTH];
    TetrisType tetrisBlock;
    map<string, int> DISPLAY_ARG;
};

#endif