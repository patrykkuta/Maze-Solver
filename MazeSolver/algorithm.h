#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <algorithm>
#include <queue>
#include "step.h"
#include "maze.h"
#include "Cell.h"

using namespace std;

class Algorithm
{

protected:
    queue<Step*> steps;
    vector<Cell*> solutionPath;

public:
    Algorithm();
    virtual ~Algorithm();

    queue<Step*> getSteps();
    vector<Cell*> getSolutionPath();

    virtual void solve(Maze &maze) = 0;
};

#endif // ALGORITHM_H
