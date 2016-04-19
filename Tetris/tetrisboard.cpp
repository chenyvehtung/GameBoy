#include "tetrisboard.h"
#include <ctime> //for time
#include <cstdlib> //for time

TetrisBoard::TetrisBoard() {
    initBoard(1);
}

TetrisBoard::TetrisBoard(int level) {
    initBoard(level);
}

void TetrisBoard::moveBlock(int direction) {
    bool flag = false;
    switch(direction) {
        case KEY_LEFT:
            if (isPossibleMove(blockY, blockX-1, blockRotation)){
                clearBlock();
                flag = true;
                blockX--;
            }
            break;
        case KEY_RIGHT:
            if (isPossibleMove(blockY, blockX+1, blockRotation)) {
                clearBlock();
                flag = true;
                blockX++;
            }
            break;
        case KEY_UP:
            {int tempRotation = (blockRotation + 1) % 4;
            if (isPossibleMove(blockY, blockX, tempRotation)) {
                clearBlock();
                flag = true;
                blockRotation = tempRotation;
            }
            break;}
        case KEY_DOWN:
            if (isPossibleMove(blockY+1, blockX, blockRotation)) {
                clearBlock();
                flag = true;
                blockY++;
            }
            break;    
        default:
            break;
    }
    if (flag) {
        placeBlock(MAIN_WIN, blockY, blockX, blockKind, blockRotation);
    }
    //to the final station, cannot move down anymore.
    if (!isPossibleMove(blockY+1, blockX, blockRotation)) {
        filledBlock();
        eraseAllLine();
        getNextBlock();
        showDisplayBoard(RIGHT_BOTTOM_WIN);
    }
    showDisplayBoard(MAIN_WIN);
}


void TetrisBoard::initBoard(int level) {
    initFilledBoard(MAIN_WIN, true, true, false, true);
    initDisplayBoard(MAIN_WIN, BLOCK_EMPTY);
    initDisplayBoard(RIGHT_BOTTOM_WIN, BLOCK_EMPTY);

    gameScore = 0;
    setGameLevel(level);

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
                    if (!mainFilledBoard[row + offsetY][column + offsetX])
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

void TetrisBoard::filledBlock() {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            if (mainDisplayBoard[row + blockY][column + blockX] != BLOCK_EMPTY) {
                mainFilledBoard[row + blockY][column + blockX] = true;
                mainDisplayBoard[row + blockY][column + blockX] = BLOCK_RED;
            }
        }
    }
}

void TetrisBoard::clearBlock() {
    for (int row = 0; row < 5;  row++) {
        for (int column = 0; column < 5; column++) {
            if (!mainFilledBoard[row + blockY][column + blockX]) {
                mainDisplayBoard[row + blockY][column + blockX] = BLOCK_EMPTY;
            }
        }
    }
}

bool TetrisBoard::isPossibleMove(int offsetY, int offsetX, int rotation) {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            int curBlock = tetrisBlock.getBlockType(blockKind, rotation, row, column);
            if (mainFilledBoard[row + offsetY][column + offsetX] &&
                curBlock != BLOCK_EMPTY)
                return false;
        }
    }
    return true;
}

void TetrisBoard::eraseLine(int rowNum) {
    for (int row = rowNum; row > 1; row--) {
        for (int column = 1; column <= MAIN_GAME_BOARD_WIDTH; column++) {
            mainDisplayBoard[row][column] = mainDisplayBoard[row - 1][column];
            mainFilledBoard[row][column] = mainFilledBoard[row - 1][column];
        }
    }
}

void TetrisBoard::eraseAllLine() {
    bool flag;
    for (int row = 2; row < MAIN_GAME_BOARD_HEIGHT; row++) {
        flag = true;
        for (int column = 1; column <= MAIN_GAME_BOARD_WIDTH; column++) {
            if (!mainFilledBoard[row][column]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            eraseLine(row);            
        }
    }
}

void TetrisBoard::getNextBlock() {
    blockY = 0;
    blockX = 1;
    blockKind = nextBlockKind;
    blockRotation = nextBlockRotation;

    nextBlockKind = rand() % BLOCK_KIND;
    nextBlockRotation = rand() % 4; 
    placeBlock(RIGHT_BOTTOM_WIN, 1, 2, nextBlockKind, nextBlockRotation);
}
