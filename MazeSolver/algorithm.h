#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <algorithm>
#include "maze.h"
#include "Cell.h"

using namespace std;

class Algorithm
{
private:
    vector<Cell> path;
    vector<Cell> visitedCells;
public:
    Algorithm();
    virtual ~Algorithm();

    virtual vector<Cell*> solve(Maze &maze) = 0;
    bool addVisitedCell(Cell cell);
};

#endif // ALGORITHM_H
