#include "tetris.h"
#include <sys/time.h>

void Tetris::startGame() {
    int direction;
    struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, NULL);  

    while(1) {

        gettimeofday(&end, NULL);
        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

        direction = GameBoyIO::getInstance().getKeyValue();
        tetrisBoard.moveBlock(direction);

        GameBoyIO::getInstance().setKeyValue(KEY_DOWN);
        gettimeofday(&start, NULL); 

    }
}    