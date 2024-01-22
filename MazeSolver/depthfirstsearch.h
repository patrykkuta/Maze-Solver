#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "algorithm.h"

using namespace std;

class DepthFirstSearch : public Algorithm
{
public:
    DepthFirstSearch(vector<array<int, 2>> path);
    ~DepthFirstSearch();

    vector<array<int, 2>> solve(Maze maze);
};

#endif // DEPTHFIRSTSEARCH_H
