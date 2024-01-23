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
    vector<vector<Cell>> maze;
    Cell* startCell;
    Cell* finishCell;

public:
    Maze(unsigned short width, unsigned short height);
    ~Maze();
    unsigned short getWidth();
    unsigned short getHeight();
    double getComplexity();
    vector<vector<Cell>> getMaze();
};

#endif // MAZE_H
