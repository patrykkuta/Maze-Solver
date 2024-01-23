#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch(vector<Cell> path) : Algorithm(path){}
DepthFirstSearch::~DepthFirstSearch() {}
vector<Cell> DepthFirstSearch::solve(Maze maze) {
    vector<Cell> v;
    Cell c(10, 20);
    v.push_back(c);
    return v;
}
