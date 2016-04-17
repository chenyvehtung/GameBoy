#include <cstring>
#include "IO/gameboyIO.h"

using std::string;

#define GameNum 2

string gameName[GameNum] = {
    "Snake",
    "Tetris"
};

void printMenu(int winNum, int highlight);

int main(int argc, char const *argv[])
{
    GameBoyIO::getInstance().initGameBoy();
    
    GameBoyIO::getInstance().printGameBorder();

    int highlight = 1;
    int choice = 0;
    printMenu(MAIN_WIN, highlight);
    
    while(1) {
        GameBoyIO::getInstance().printGameBorder();
        choice = GameBoyIO::getInstance().getKeyValue();
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
        printMenu(MAIN_WIN, highlight);
    }
    GameBoyIO::getInstance().endGameBoy();
    return 0;
}

void printMenu(int winNum, int highlight) {
    int rowNo = (MAIN_WIN_HIGHT - GameNum) / 2;
    int columnNo = 0; 
    for (int cnt = 0; cnt < GameNum; cnt++) {
        if (highlight == cnt + 1) {
            GameBoyIO::getInstance().printWords(winNum, rowNo, columnNo, "==>"+gameName[cnt], A_BOLD);
        }
        else 
            GameBoyIO::getInstance().printWords(winNum, rowNo, columnNo, "   "+gameName[cnt]);
        rowNo++;
    }
    GameBoyIO::getInstance().refreshWin(winNum);
}

