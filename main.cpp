#include <cstring>
#include "IO/gameboyIO.h"

using std::string;

#define GameNum 2

string gameName[GameNum] = {
    "Snake",
    "Tetris"
};

void printMenu(GameBoyIO gameBoyIO, int highlight);

int main(int argc, char const *argv[])
{
    GameBoyIO gameBoyIO;
    GB_WINDOW* mainWin = gameBoyIO.gbGetWinLocate(MAIN_WIN);
    int highlight = 1;
    int choice = 0;
    printMenu(gameBoyIO, highlight);
    while(1) {
        choice = GB_getch(mainWin);
        switch(choice) {
            case GB_KEY_UP:
                if (highlight == 1) {
                    highlight = GameNum - 1;
                }
                else 
                    highlight++;
                break;
            case GB_KEY_DOWN:
                if (highlight == GameNum - 1) 
                    highlight = 0;
                else 
                    highlight--;
            default:
                break;
        }
        printMenu(gameBoyIO, highlight);
    }
    getch();
    endwin();
    return 0;
}

void printMenu(GameBoyIO gameBoyIO, int highlight) {
    int rowNo = (MAIN_WIN_HIGHT - GameNum) / 2;
    int columnNo = 2; 
    GB_WINDOW* winLocate = gameBoyIO.gbGetWinLocate(MAIN_WIN);
    for (int cnt = 0; cnt < GameNum; cnt++) {
        if (highlight == cnt + 1) {
            gameBoyIO.gbPrint(winLocate, rowNo, columnNo, gameName[cnt], A_BOLD);
        }
        else 
            gameBoyIO.gbPrint(winLocate, rowNo, columnNo, gameName[cnt]);
    }
    gameBoyIO.gbRefresh(winLocate);
}

