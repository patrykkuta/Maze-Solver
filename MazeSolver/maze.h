#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <queue>
#include "step.h"
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
    Cell* generationStartCell;
    vector<Step> generationSteps;

public:
    Maze(unsigned short width, unsigned short height);
    virtual ~Maze();
    unsigned short getWidth();
    unsigned short getHeight();
    vector<vector<Cell*>> getMaze();
    Cell* getStartCell();
    Cell* getFinishCell();
    virtual void generateMaze() = 0;
    virtual Cell* getGenerationStartCell() = 0;
    vector<Step> getGenerationSteps();
};

#endif // MAZE_H
