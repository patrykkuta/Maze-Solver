#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch(vector<array<int, 2>> path) : Algorithm(path) {}

vector<array<int, 2>> BreadthFirstSearch::solve(Maze maze) {
    vector<array<int, 2>> v;
    array<int, 2> a = {1, 2};
    v.push_back(a);
    return v;
}
