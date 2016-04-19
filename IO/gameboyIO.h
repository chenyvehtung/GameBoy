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
#define RIGHT_WIN_HEIGHT (MAIN_WIN_HIGHT / 2)
#define RIGHT_WIN_WIDTH 16


#define MAIN_GAME_BOARD_HEIGHT (MAIN_WIN_HIGHT - 2)
#define MAIN_GAME_BOARD_WIDTH (MAIN_WIN_WIDTH / 2 - 1)
#define RIGHT_BOTTOM_GAME_BOARD_HEIGHT (RIGHT_WIN_HEIGHT - 2)
#define RIGHT_BOTTOM_GAME_BOARD_WIDTH (RIGHT_WIN_WIDTH / 2 - 1)


#define BLOCK_EMPTY 0
#define BLOCK_BLUE 1
#define BLOCK_CYAN 2
#define BLOCK_RED 3

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
    //http://stackoverflow.com/questions/270947/can-any-one-provide-me-a-sample-of-singleton-in-c/271104#271104
    //the implement of singleton pattern using reference
    static GameBoyIO& getInstance() {
        static GameBoyIO instance;
        return instance;
    }
    void initGameBoy();
    void printGameBorder();
    /*
    print words to the screen
     */
    void printWords(int winNum, int startY, int startX, string words, attr_t attribute = A_NORMAL);
    void drawBlock(int winNum, int startY, int startX, int blockType);
    void refreshWin(int winNum);
    /*
    return the input keyValue
     */
    int getKeyValue();
    void setKeyValue(int kv);
    void endGameBoy();

    void setTimeout(int num);


private:
    GB_WINDOW *mainWin, *rtWin, *rbWin; 
    int keyValue;
    
    GameBoyIO(){}
    GameBoyIO(GameBoyIO const&);
    void operator=(GameBoyIO const&);   
    GB_WINDOW* newWinLocate(int height, int width, int startY, int startX, int winNum);
    GB_WINDOW* getWinLocate(int winNum);



};

#endif