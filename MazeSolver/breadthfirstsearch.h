#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "algorithm.h"

class BreadthFirstSearch : public Algorithm
{
public:
    BreadthFirstSearch(vector<Cell> path);
    ~BreadthFirstSearch();

    vector<Cell> solve(Maze maze);
};

#endif // BREADTHFIRSTSEARCH_H
