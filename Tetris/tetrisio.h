#ifndef TETRIS_IO_H_
#define TETRIS_IO_H_

#include <pthread.h> 
#include <string>
#include <map>
using std::map;
using std::string;

class TetrisIO {

public:
    TetrisIO();
    ~TetrisIO();
    void drawBoard(int** gameBoard, const map<string, int>& displayVal);
    char getDirect();
    void setDirect(char direct);
    
private:
    void* getDirection(void);
    static void* getHelper(void* context);
    void createThread();
    void waitThread();
    char imdiChar();
    int getConstMapVal(const map<string, int>& displayVal, string key);

    pthread_t tetrisThread;
    pthread_mutex_t tetrisLock;
    char direction;
};

#endif