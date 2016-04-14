#ifndef TETRIS_TYPE_H_
#define TETRIS_TYPE_H_


#define BLOCK_KIND 2

class TetrisType {

public:
    int getBlockType(int kind, int rotation, int row, int column);

};

#endif