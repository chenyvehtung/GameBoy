#include <cstring>
#include "IO/gameboyIO.h"

using std::string;

#define GameNum 2

string gameName[GameNum] = {
    "Snake",
    "Tetris"
};

void printMenu(GB_WINDOW* gbWin, int highlight);

int main(int argc, char const *argv[])
{
    GameBoyIO::getInstance().initGameBoy();
    
    GameBoyIO::getInstance().printGameBorder();
    GB_WINDOW* mainWin = GameBoyIO::getInstance().getWinLocate(MAIN_WIN);  
    int highlight = 1;
    int choice = 0;
    printMenu(mainWin, highlight);
    
    while(1) {
        GameBoyIO::getInstance().printGameBorder();
        choice = wgetch(mainWin->win);
        switch(choice) {
            case KEY_UP:
                if (highlight == 1) {
                    highlight = GameNum;
                }
                else 
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight == GameNum) 
                    highlight = 1;
                else 
                    highlight++;
            default:
                break;
        }
        printMenu(mainWin, highlight);
    }
    getch();
    endwin();
    return 0;
}

void printMenu(GB_WINDOW* gbWin, int highlight) {
    int rowNo = (MAIN_WIN_HIGHT - GameNum) / 2;
    int columnNo = 0; 
    for (int cnt = 0; cnt < GameNum; cnt++) {
        if (highlight == cnt + 1) {
            wattron(gbWin->win, A_BOLD);
            mvwprintw(gbWin->win, rowNo, columnNo, "==>%s", gameName[cnt].c_str());
            wattroff(gbWin->win, A_BOLD);
        }
        else 
            mvwprintw(gbWin->win, rowNo, columnNo, "   %s", gameName[cnt].c_str());
        rowNo++;
    }
    wrefresh(gbWin->win);
}

