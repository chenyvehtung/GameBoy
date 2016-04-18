#include <cstring>
#include <sstream>
#include <unistd.h> //for usleep
#include "IO/gameboyIO.h"
#include "Tetris/tetrisboard.h"

using std::string;
using std::stringstream;

#define GameNum 3

string gameName[GameNum] = {
    "Snake",
    "Tetris",
    "Exit"
};

void printMenu(int winNum, int highlight);
string intToStr(int num);

int main(int argc, char const *argv[])
{
    GameBoyIO::getInstance().initGameBoy();
    
    int highlight = 0;
    int keyValue = 0;

    GameBoyIO::getInstance().printGameBorder();
    printMenu(MAIN_WIN, highlight);    
        
    while(1) {
        int choice = -1;
        bool flag = false;
        keyValue = GameBoyIO::getInstance().getKeyValue();
        switch(keyValue) {
            case KEY_UP:
                if (highlight == 0) {
                    highlight = GameNum - 1;
                }
                else 
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight == GameNum - 1) 
                    highlight = 0;
                else 
                    highlight++;
                break;
            case 10: //key Enter
                choice = highlight;
                break;
            default:
                break;
        }

        switch(choice) {
            case 0:
                //call snake
                break;
            case 1:
                //call tetris
                {
                TetrisBoard* temp = new TetrisBoard(10);
                usleep(5000000);
                break;
                }
            case 2:  //make it point to Exit
                flag = true;
                break;
            default:
                break;
        }



        GameBoyIO::getInstance().printGameBorder();
        printMenu(MAIN_WIN, highlight);

        if (flag) {
            break;
        }

    }
    
    GameBoyIO::getInstance().endGameBoy();
    return 0;
}


void printMenu(int winNum, int highlight) {
    int rowNo = (MAIN_WIN_HIGHT - GameNum) / 2;
    int columnNo = 2; 
    for (int cnt = 0; cnt < GameNum; cnt++) {
        string strNum = intToStr(cnt + 1);
        if (highlight == cnt) {
            GameBoyIO::getInstance().printWords(winNum, rowNo, columnNo, 
                "-> "+strNum+". "+gameName[cnt], COLOR_PAIR(BLOCK_CYAN) | A_BOLD);
        }
        else {
            GameBoyIO::getInstance().printWords(winNum, rowNo, columnNo, 
                "   "+strNum+". "+gameName[cnt]);
        }
        rowNo++;
    }
    GameBoyIO::getInstance().refreshWin(winNum);
}


//http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
//convert int to string
string intToStr(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}
