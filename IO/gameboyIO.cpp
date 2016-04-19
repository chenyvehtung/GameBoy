#include "gameboyIO.h"
#include <cstdio> //for getchar
#include <termios.h>     //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

void GameBoyIO::initGameBoy() {
    initscr();
    clear();
    noecho();
    curs_set(FALSE);
    cbreak();
    rbWin = newWinLocate(MAIN_WIN_HIGHT/2, RIGHT_WIN_WIDTH, 
                        MAIN_WIN_HIGHT/2, MAIN_WIN_WIDTH, RIGHT_BOTTOM_WIN);
    rtWin = newWinLocate(MAIN_WIN_HIGHT/2, RIGHT_WIN_WIDTH,
                        0, MAIN_WIN_WIDTH, RIGHT_TOP_WIN);
    mainWin = newWinLocate(MAIN_WIN_HIGHT, MAIN_WIN_WIDTH, 0, 0, MAIN_WIN);
    keypad(mainWin->win, TRUE);

    start_color();
    init_pair(BLOCK_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(BLOCK_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLOCK_RED, COLOR_RED, COLOR_BLACK);

}


void GameBoyIO::printGameBorder() {
    // show right bottom box
    winBorder wbs = rbWin->wbs;
    wborder(rbWin->win, wbs.ls, wbs.rs, wbs.ts, wbs.bs, wbs.tl, wbs.tr, wbs.bl, wbs.br);
    wrefresh(rbWin->win);
    // show right top box
    wbs = rtWin->wbs;
    wborder(rtWin->win, wbs.ls, wbs.rs, wbs.ts, wbs.bs, wbs.tl, wbs.tr, wbs.bl, wbs.br);
    wrefresh(rtWin->win);
    //show main box
    wbs = mainWin->wbs;
    wborder(mainWin->win, wbs.ls, wbs.rs, wbs.ts, wbs.bs, wbs.tl, wbs.tr, wbs.bl, wbs.br);
    wrefresh(mainWin->win);
}

void GameBoyIO::printWords(int winNum, int startY, int startX, string words, attr_t attribute) {
    GB_WINDOW* gbWin = getWinLocate(winNum);
    if (attribute == A_NORMAL) {
        mvwprintw(gbWin->win, startY, startX, "%s", words.c_str());
    }
    else {
        wattron(gbWin->win, attribute);
        mvwprintw(gbWin->win, startY, startX, "%s", words.c_str());
        wattroff(gbWin->win, attribute);
    }
}

void GameBoyIO::drawBlock(int winNum, int startY, int startX, int blockType) {
    switch(blockType) {
        case BLOCK_EMPTY:
            printWords(winNum, startY, startX, "  ");
            break;
        case BLOCK_BLUE:
            printWords(winNum, startY, startX, "* ", COLOR_PAIR(BLOCK_BLUE));
            break;
        case BLOCK_CYAN:
            printWords(winNum, startY, startX, "# ", COLOR_PAIR(BLOCK_CYAN));
            break;
        case BLOCK_RED:
            printWords(winNum, startY, startX, "# ", COLOR_PAIR(BLOCK_RED));
            break;
        default:
            break;
    }
}

void GameBoyIO::refreshWin(int winNum) {
    GB_WINDOW* gbWin = getWinLocate(winNum);
    wrefresh(gbWin->win);
}


int GameBoyIO::getKeyValue() {
    int tempValue = wgetch(mainWin->win);
    if (tempValue != -1) 
        keyValue = tempValue;
    return keyValue;
}

void GameBoyIO::setKeyValue(int kv) {
    keyValue = kv;
}

void GameBoyIO::endGameBoy() {
    endwin();
}

void GameBoyIO::setTimeout(int num) {
    wtimeout(mainWin->win, num);
}

GB_WINDOW* GameBoyIO::newWinLocate(int height, int width, 
            int startY, int startX, int winNum) {
    GB_WINDOW* winLocate = new GB_WINDOW;
    winLocate->win = newwin(height, width, startY, startX);
    switch(winNum) {
        case MAIN_WIN:
            winLocate->wbs = winBorder(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                                       ACS_ULCORNER, ACS_TTEE, ACS_LLCORNER, ACS_BTEE);
            break;
        case RIGHT_TOP_WIN:
            winLocate->wbs = winBorder(' ', ACS_VLINE, ACS_HLINE, ACS_HLINE, 
                                    ACS_HLINE, ACS_URCORNER, ACS_HLINE, ACS_RTEE);
            break;
        case RIGHT_BOTTOM_WIN:
            winLocate->wbs = winBorder(' ', ACS_VLINE, ' ', ACS_HLINE, 
                                    ' ', ACS_VLINE, ACS_HLINE, ACS_LRCORNER);
            break;
        default:
            break;
    }
    return winLocate;
}

//http://stackoverflow.com/questions/27428071/return-a-struct-defined-in-a-separate-header-file-unknown-type-name
//add a classname in front of the struct name
GB_WINDOW* GameBoyIO::getWinLocate(int winNum) {
    switch(winNum) {
        case MAIN_WIN:
            return mainWin;
        case RIGHT_TOP_WIN:
            return rtWin;
        case RIGHT_BOTTOM_WIN:
            return rbWin;
        default:
            return NULL;
    }
}


