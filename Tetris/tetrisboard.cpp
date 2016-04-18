#include "tetrisboard.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

TetrisBoard::TetrisBoard() {
    initBoard();
}

void TetrisBoard::initBoard() {

    //setup game wall and initialize all block as empty
    for (int row = 0; row <= MAIN_GAME_BOARD_HEIGHT; row++) {
        for (int column = 0; column <= MAIN_GAME_BOARD_WIDTH; column++) {
            gameBoard[row][column] = BLOCK_EMPTY;
            isFilled[row][column] = false;
            if (column == 0 || column == MAIN_GAME_BOARD_WIDTH) {
                isFilled[row][column] = true;
            }
            if (row == MAIN_GAME_BOARD_HEIGHT) {
                isFilled[row][column] = true;
            }
        }
    }

    srand(time(NULL));
    blockKind = rand() % BLOCK_KIND;
    blockRotation = rand() % 4;
    offsetX = 1; 
    offsetY = 1;
    placeBlock(offsetX, offsetY, blockKind, blockRotation);

    nextBlockKind = rand() % BLOCK_KIND;
    nextBlockRotation = rand() % 4; 

}



int** TetrisBoard::getGameBoard() {
    int** board2D = 0;
    board2D = new int* [BOARD_HEIGHT];
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board2D[i] = new int[BOARD_WIDTH];
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board2D[i][j] = gameBoard[i][j];
        }
    }
    return board2D;
}



void TetrisBoard::moveBlock(int direction) {
    clearBlock(offsetX, offsetY);
    int tempX = offsetX, tempY = offsetY, tempRotation = blockRotation;
    switch(direction) {
        case LEFT:
            offsetY -= 1;
            break;
        case RIGHT:
            offsetY += 1;
            break;
        case DOWN:
            offsetX += 1;
            break;
        case UP:
            blockRotation = (blockRotation + 1) % 4;
            break;
        default:
            break;
    }
    if (isPossibleMove()) {
        placeBlock(offsetX, offsetY, blockKind, blockRotation);
    }
    else {
        offsetX = tempX;
        offsetY = tempY;
        blockRotation = tempRotation;
        if (direction == DOWN) {
            placeBlock(offsetX, offsetY, blockKind, blockRotation);
            filledBlock(offsetX, offsetY);
            eraseAllLine();
            getNextBlock();
        }
    }
}


void TetrisBoard::placeBlock(int offsetX, int offsetY, int kind, int rotation) {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            int curBlock = tetrisBlock.getBlockType(kind, rotation, row, column);
            if (!isFilled[row + offsetY][column + offsetX])
                gameBoard[row + offsetY][column + offsetX] = curBlock;
        }
    }
}

void TetrisBoard::filledBlock(int offsetX, int offsetY) {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            if (gameBoard[row + offsetX][column + offsetY] != DISPLAY_ARG["BOARD_SPACE"])
                isFilled[row + offsetX][column + offsetY] = true;
        }
    }
}

void TetrisBoard::clearBlock(int offsetX, int offsetY) {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            if (!isFilled[row + offsetX][column + offsetY])
                gameBoard[row + offsetX][column + offsetY] = DISPLAY_ARG["BOARD_SPACE"];
        }
    }
}

bool TetrisBoard::isPossibleMove() {
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            int curBlock = tetrisBlock.getBlockType(blockKind, blockRotation, row, column);
            if ( isFilled[row + offsetX][column + offsetY] && 
                (curBlock != DISPLAY_ARG["BOARD_SPACE"]) )
                return false;
        }
    }
    return true;
}

void TetrisBoard::getNextBlock() {
    offsetX = 0;
    offsetY = DISPLAY_ARG["GAME_MARGIN"] + 1;
    blockKind = nextBlockKind;
    blockRotation = nextBlockRotation;

    nextBlockKind = rand() % BLOCK_KIND;
    nextBlockRotation = rand() % 4; 
    clearBlock(nextOffsetX, nextOffsetY);
    placeBlock(nextOffsetX, nextOffsetY, nextBlockKind, nextBlockRotation);
}

void TetrisBoard::eraseAllLine() {
    bool flag;
    for (int row = 0; row < DISPLAY_ARG["BOARD_HEIGHT"] - 1; row++) {
        flag = true;
        for (int column = DISPLAY_ARG["GAME_MARGIN"] + 1;
        column < DISPLAY_ARG["GAME_MARGIN"] + DISPLAY_ARG["GAME_WIDTH"]; column++) {
            if (!isFilled[row][column]) {
                flag = false;
                break;
            }
        }
        if (flag)
            eraseLine(row);
    }
}

void TetrisBoard::eraseLine(int rowNo) {
    for (int row = rowNo; row > 0; row--) {
        for (int column = DISPLAY_ARG["GAME_MARGIN"] + 1;
            column < DISPLAY_ARG["GAME_MARGIN"] + DISPLAY_ARG["GAME_WIDTH"]; column++) {
            gameBoard[row][column] = gameBoard[row - 1][column];
            isFilled[row][column] = isFilled[row - 1][column];
        }
    }
}