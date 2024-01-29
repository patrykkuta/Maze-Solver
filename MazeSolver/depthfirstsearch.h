#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "pathfindingalgorithm.h"
#include <stack>

using namespace std;

class DepthFirstSearch : public PathFindingAlgorithm
{
public:
    DepthFirstSearch();
    ~DepthFirstSearch();

    void solve(Maze &maze) override;
};

#endif // DEPTHFIRSTSEARCH_H
