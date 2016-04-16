#ifndef GAME_BOY_IO_H_
#define GAME_BOY_IO_H_

#include <ncurses.h>
#include <string>
using std::string;

#define MAIN_WIN 1
#define RIGHT_TOP_WIN 2
#define RIGHT_BOTTOM_WIN 3
#define MAIN_WIN_HIGHT 20
#define MAIN_WIN_WIDTH 40
#define RIGHT_WIN_WIDTH 10

#define GB_WINDOW WINDOW
#define GB_KEY_UP KEY_UP
#define GB_KEY_DOWN KEY_DOWN
#define GB_KEY_ENTER 10

#define GB_getch(win) wgetch(win)

class GameBoyIO {

public:
    GameBoyIO();
    WINDOW* gbGetWinLocate(int winType);
    void gbPrint(WINDOW* winLocate, int startY, int startX, string words, 
                 attr_t attribute = A_NORMAL);
    void gbRefresh(WINDOW* winLocate = stdscr);


private:
    WINDOW *mainWin, *rtWin, *rdWin;
    /*
     * ls: character to be used for the left side of the window 
     * rs: character to be used for the right side of the window 
     * ts: character to be used for the top side of the window 
     * bs: character to be used for the bottom side of the window 
     * tl: character to be used for the top left corner of the window 
     * tr: character to be used for the top right corner of the window 
     * bl: character to be used for the bottom left corner of the window 
     * br: character to be used for the bottom right corner of the window
     */
    struct winBorderStruct {
        chtype ls, rs, ts, bs, tl, tr, bl, br;
        winBorderStruct(chtype tls, chtype trs, chtype tts, chtype tbs,
            chtype ttl, chtype ttr, chtype tbl, chtype tbr) {
            ls = tls; rs = trs; ts = tts; bs = tbs;
            tl = ttl; tr = ttr; bl = tbl; br = tbr;
        }
    };

    WINDOW* createWin(int height, int width, 
    int startY, int startX, const winBorderStruct &wbs);
};


#endif