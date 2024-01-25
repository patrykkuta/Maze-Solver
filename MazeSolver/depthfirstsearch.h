#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "algorithm.h"
#include <stack>

using namespace std;

class DepthFirstSearch : public Algorithm
{
public:
    DepthFirstSearch();
    ~DepthFirstSearch();

    void solve(Maze &maze) override;

private:
    vector<Cell*> backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell);
};

#endif // DEPTHFIRSTSEARCH_H
