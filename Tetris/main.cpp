#include "tetrisio.h"
#include "tetrisboard.h"
#include <unistd.h> //for usleep

int TURNTIME = 500000; //500ms

int main(int argc, char const *argv[])
{

    TetrisIO tetrisIO;
    TetrisBoard tetrisBoard;
    tetrisIO.drawBoard(tetrisBoard.getGameBoard(), tetrisBoard.getDisplayArg());
    tetrisIO.setDirect(TetrisBoard::DOWN);
    while(1) {
        int direction = (int)tetrisIO.getDirect();
        if (direction == 'Q' || direction == 'q') 
            break;
        tetrisBoard.moveBlock(direction);

        tetrisIO.drawBoard(tetrisBoard.getGameBoard(), tetrisBoard.getDisplayArg());
        tetrisIO.setDirect(TetrisBoard::DOWN);
        usleep(TURNTIME);
    }
    return 0;
}