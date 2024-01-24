#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch(){}
DepthFirstSearch::~DepthFirstSearch() {}
vector<Cell*> DepthFirstSearch::solve(Maze maze) {
    vector<Cell*> v;
    Cell c(10, 20);
    v.push_back(&c);
    return v;
}
