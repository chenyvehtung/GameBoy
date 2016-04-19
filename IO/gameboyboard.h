#ifndef GAME_BOY_BOARD_H_
#define GAME_BOY_BOARD_H_

#include "gameboyIO.h"
#include <sstream>
using std::stringstream;

class GameBoyBoard {
public:
    GameBoyBoard();
    void initFilledBoard(int winNum, bool ls, bool rs, bool ts, bool bs);
    void initDisplayBoard(int winNum, int type);
    void showDisplayBoard(int winNum);
    void setGameLevel(int num);
    int getGameLevel();


protected:
    int mainDisplayBoard[MAIN_GAME_BOARD_HEIGHT + 10][MAIN_GAME_BOARD_WIDTH + 10];
    bool mainFilledBoard[MAIN_GAME_BOARD_HEIGHT + 10][MAIN_GAME_BOARD_WIDTH + 10];
    int rbDisplayBoard[RIGHT_BOTTOM_GAME_BOARD_HEIGHT + 10][RIGHT_BOTTOM_GAME_BOARD_WIDTH + 10];
    int gameScore;
    int gameLevel;

    string intToStr(int num) {
        stringstream ss;
        ss << num;
        return ss.str();
    }
};

#endif