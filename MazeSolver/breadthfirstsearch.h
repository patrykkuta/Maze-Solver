#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "pathfindingalgorithm.h"
#include <unordered_map>

class BreadthFirstSearch : public PathFindingAlgorithm
{
public:
    BreadthFirstSearch();
    ~BreadthFirstSearch();

    void solve(Maze &maze) override;
};

#endif // BREADTHFIRSTSEARCH_H
