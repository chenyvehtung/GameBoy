#include "tetris.h"

void Tetris::startGame() {
    int direction;
    while(1) {
        direction = GameBoyIO::getInstance().getKeyValue();
        tetrisBoard.moveBlock(direction);
    }
}    