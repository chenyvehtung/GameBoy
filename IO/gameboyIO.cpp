#include "gameboyIO.h"

GameBoyIO::GameBoyIO() {
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();

    /* initialize right bottom window */
    winBorderStruct rbWinBorder(' ', ACS_VLINE, ' ', ACS_HLINE, 
                                ' ', ACS_VLINE, ACS_HLINE, ACS_LRCORNER);
    rdWin = createWin(MAIN_WIN_HIGHT/2, RIGHT_WIN_WIDTH, 
                      MAIN_WIN_HIGHT/2, MAIN_WIN_WIDTH, rbWinBorder);
    /* initialize right top window */
    winBorderStruct rtWinBorder(' ', ACS_VLINE, ACS_HLINE, ACS_HLINE, 
                                ACS_HLINE, ACS_URCORNER, ACS_HLINE, ACS_RTEE);
    rtWin = createWin(MAIN_WIN_HIGHT/2, RIGHT_WIN_WIDTH,
                      0, MAIN_WIN_WIDTH, rtWinBorder);
    /* initialize main window */
    winBorderStruct mWinBorder(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                               ACS_ULCORNER, ACS_TTEE, ACS_LLCORNER, ACS_BTEE);
    mainWin = createWin(MAIN_WIN_HIGHT, MAIN_WIN_WIDTH, 0, 0, mWinBorder);

}

WINDOW* GameBoyIO::gbGetWinLocate(int winType) {
    WINDOW *winLocate;
    switch(winType) {
        case MAIN_WIN:
            winLocate = mainWin;
            break;
        case RIGHT_TOP_WIN:
            winLocate = rtWin;
            break;
        case RIGHT_BOTTOM_WIN:
            winLocate = rdWin;
            break;
        default:
            winLocate = NULL;
            break;
    }
    return winLocate;
}

WINDOW* GameBoyIO::createWin(int height, int width, int startY, int startX, 
    const winBorderStruct &wbs) {
    WINDOW* winLocate;
    winLocate = newwin(height, width, startY, startX);
    wborder(winLocate, wbs.ls, wbs.rs, wbs.ts, wbs.bs, wbs.tl, wbs.tr, wbs.bl, wbs.br);
    wrefresh(winLocate); //Show the box
    return winLocate;
}

void GameBoyIO::gbPrint(WINDOW* winLocate, int startY, int startX, string words, attr_t attribute) {
    if (attribute == A_NORMAL) 
        mvwprintw(winLocate, startY, startX, "%s", words.c_str());
    else {
        wattron(winLocate, attribute); 
        mvwprintw(winLocate, startY, startX, "%s", words.c_str());
        wattroff(winLocate, attribute);
    }
}

void GameBoyIO::gbRefresh(WINDOW* winLocate) {
    if (winLocate == stdscr) 
        refresh();
    else
        wrefresh(winLocate);
}