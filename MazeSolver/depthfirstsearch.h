#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "algorithm.h"

using namespace std;

class DepthFirstSearch : public Algorithm
{
public:
    DepthFirstSearch(vector<Cell> path);
    ~DepthFirstSearch();

    vector<Cell> solve(Maze maze);
};

#endif // DEPTHFIRSTSEARCH_H
