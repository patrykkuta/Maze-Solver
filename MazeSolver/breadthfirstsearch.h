#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "algorithm.h"
#include <unordered_map>

class BreadthFirstSearch : public Algorithm
{
public:
    BreadthFirstSearch(Maze &maze);
    ~BreadthFirstSearch();

private:
    void solve(Maze &maze) override;
    vector<Cell*> backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell);
};

#endif // BREADTHFIRSTSEARCH_H
