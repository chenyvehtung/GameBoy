#include "tetrisio.h"
#include <iostream>
#include <cstdlib> //for system
#include <cstdio> //for getchar
#include <termios.h>     //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

using std::cout;
using std::endl;

TetrisIO::TetrisIO() {
    tetrisThread = 0;
    createThread();
}

TetrisIO::~TetrisIO() {
    waitThread();
}

/*
    The case statements require integral value which must be known at compile-time, 
    which is what is meant by constant here. But the const members of a class are 
    not really constant in that sense. They're are simply read-only.
    http://stackoverflow.com/questions/8049834/case-expression-not-constant
    so here we must use if else instead of switch
 */
void TetrisIO::drawBoard(int** gameBoard, const map<string, int>& displayVal) {
    system("clear");
    for (int row = 0; row < getConstMapVal(displayVal, "BOARD_HEIGHT"); row++) {
        for (int column = 0; column < getConstMapVal(displayVal, "BOARD_WIDTH"); column++) {
            int type =  gameBoard[row][column];
            if (type == getConstMapVal(displayVal, "BOARD_WALL"))
                cout << "[]";
            else if (type == getConstMapVal(displayVal, "BLOCK_SIMPLE"))
                cout << "# ";
            else if (type == getConstMapVal(displayVal, "BLOCK_PIVOT"))
                cout << "* ";
            else if (type == getConstMapVal(displayVal, "BOARD_SPACE"))
                cout << "  ";
            else 
                continue;
        }
        cout << endl;
    }
}

char TetrisIO::getDirect() {
    return direction;
}

void TetrisIO::setDirect(char direct) {
    direction = direct;
}

void* TetrisIO::getDirection(void) {
    while(1) {
        pthread_mutex_lock(&tetrisLock);
        direction = imdiChar();
        if (direction == 'Q' || direction == 'q') {
            break;
        }
        pthread_mutex_unlock(&tetrisLock);
    }
    pthread_exit(NULL);
}

/*
    http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
 */
void* TetrisIO::getHelper(void* context) {
    return ((TetrisIO*)context)->getDirection();
}

void TetrisIO::createThread() {
    int tempStatus;
    tempStatus = pthread_create(&tetrisThread, NULL, &TetrisIO::getHelper, this);
    if (!tempStatus) {
        cout << "Error: Failed to create a thread!" << endl;
    }
}

void TetrisIO::waitThread() {
    if (tetrisThread != 0) {
        pthread_join(tetrisThread, NULL);
    }
}

//get char without Enter and ignore echo
//http://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar
char TetrisIO::imdiChar() {
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL
    and ignore echo back*/
    newt.c_lflag &= ~(ICANON | ECHO);   
    //newt.c_lflag &= ~(ICANON);       

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    char tempChar = getchar();

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return tempChar;
}

/*
    When you're using operator[], std::map looks for item with given key. 
    If it does not find any, it creates it. Hence the problem with const.
    http://stackoverflow.com/questions/687789/c-const-stdmap-reference-fails-to-compile
 */
int TetrisIO::getConstMapVal(const map<string, int>& displayVal, string key) {
    int result = -1;
    map<string, int>::const_iterator it;
    it = displayVal.find(key);
    if (it != displayVal.end()) {
        result = it->second;
    }
    return result;
}