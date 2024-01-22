#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch(vector<array<int, 2>> path) : Algorithm(path){}
DepthFirstSearch::~DepthFirstSearch() {}
vector<array<int, 2>> DepthFirstSearch::solve(Maze maze) {
    vector<array<int, 2>> v;
    array<int, 2> a = {1, 2};
    v.push_back(a);
    return v;
}
