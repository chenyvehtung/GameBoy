#include "gameboyIO.h"

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
