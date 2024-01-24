#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "algorithm.h"

using namespace std;

class DepthFirstSearch : public Algorithm
{
public:
    DepthFirstSearch();
    ~DepthFirstSearch();

    vector<Cell*> solve(Maze &maze) override;
};

#endif // DEPTHFIRSTSEARCH_H
