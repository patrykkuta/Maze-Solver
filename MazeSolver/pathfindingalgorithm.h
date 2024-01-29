#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <vector>
#include <algorithm>
#include <queue>
#include "step.h"
#include "maze.h"
#include "Cell.h"

class PathFindingAlgorithm
{
protected:
    queue<Step*> solvingSteps;
    vector<Cell*> solution;

    vector<Cell*> backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell);

public:
    PathFindingAlgorithm();
    virtual ~PathFindingAlgorithm();

    queue<Step*> getSolvingSteps();
    vector<Cell*> getSolution();

    virtual void solve(Maze &maze) = 0;
};
#endif // PATHFINDINGALGORITHM_H
