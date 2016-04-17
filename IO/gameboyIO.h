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
typedef struct _winBorderStruct{
    chtype ls, rs, ts, bs, tl, tr, bl, br;
    _winBorderStruct() {
        ls = ' '; rs = ' '; ts = ' '; bs = ' ';
        tl = ' '; tr = ' '; bl = ' '; br = ' '; 
    }
    _winBorderStruct(chtype tls, chtype trs, chtype tts, chtype tbs,
        chtype ttl, chtype ttr, chtype tbl, chtype tbr) {
        ls = tls; rs = trs; ts = tts; bs = tbs;
        tl = ttl; tr = ttr; bl = tbl; br = tbr;
    }
}winBorder;
typedef struct _GBWindowStruct {
    WINDOW *win;
    winBorder wbs;
    _GBWindowStruct() {
        win = newwin(0, 0, 0, 0);
        wbs = winBorder();
    }
}GB_WINDOW;


class GameBoyIO {

public:
    static GameBoyIO& getInstance() {
        static GameBoyIO instance;
        return instance;
    }
    void initGameBoy();
    GB_WINDOW* getWinLocate(int winNum);
    void printGameBorder();

private:
    GB_WINDOW *mainWin, *rtWin, *rbWin; 
    
    GameBoyIO(){}
    GameBoyIO(GameBoyIO const&);
    void operator=(GameBoyIO const&);   
    GB_WINDOW* newWinLocate(int height, int width, int startY, int startX, int winNum);
};

#endif