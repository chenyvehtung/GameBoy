#include "tetrisboard.h"
#include <ctime> //for time
#include <cstdlib> //for time

TetrisBoard::TetrisBoard() {
    initBoard(1);
}

TetrisBoard::TetrisBoard(int score) {
    initBoard(score);
}


void TetrisBoard::initBoard(int level) {
    initFilledBoard(MAIN_WIN, true, true, false, true);
    initDisplayBoard(MAIN_WIN, BLOCK_RED);
    initDisplayBoard(RIGHT_BOTTOM_WIN, BLOCK_EMPTY);

    gameScore = 0;
    gameLevel = level;

    srand(time(NULL));
    blockKind = rand() % BLOCK_KIND;
    blockRotation = rand() % 4;
    blockY = 0;
    blockX = 1;
    placeBlock(MAIN_WIN, blockY, blockX, blockKind, blockRotation);

    nextBlockKind = rand() % BLOCK_KIND;
    nextBlockRotation = rand() % 4; 
    placeBlock(RIGHT_BOTTOM_WIN, 1, 2, nextBlockKind, nextBlockRotation);

    showDisplayBoard(RIGHT_BOTTOM_WIN);
    showDisplayBoard(RIGHT_TOP_WIN);
    showDisplayBoard(MAIN_WIN);
}


void TetrisBoard::placeBlock(int winNum, int offsetY, int offsetX, int kind, int rotation) {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            int curBlock = tetrisBlock.getBlockType(kind, rotation, row, column);
            switch(winNum) {
                case MAIN_WIN:
                    mainDisplayBoard[row + offsetY][column + offsetX] = curBlock;
                    break;
                case RIGHT_BOTTOM_WIN:
                    rbDisplayBoard[row + offsetY][column + offsetX] = curBlock;
                    break;
                default:
                    break;
            }
        }
    }
}