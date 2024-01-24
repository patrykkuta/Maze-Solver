#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Cell.h"

using namespace std;

class Maze
{
protected:
    unsigned short width;
    unsigned short height;
    vector<vector<Cell*>> maze;
    Cell* startCell;
    Cell* finishCell;

public:
    Maze(unsigned short width, unsigned short height);
    virtual ~Maze();
    unsigned short getWidth();
    unsigned short getHeight();
    vector<vector<Cell*>> getMaze();
    Cell* getStartCell();
    Cell* getFinishCell();
};

#endif // MAZE_H
