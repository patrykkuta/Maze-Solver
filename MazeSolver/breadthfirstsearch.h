#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "algorithm.h"

class BreadthFirstSearch : public Algorithm
{
public:
    BreadthFirstSearch(vector<array<int, 2>> path);

    vector<array<int, 2>> solve(Maze maze);
};

#endif // BREADTHFIRSTSEARCH_H
