#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch(vector<Cell> path) : Algorithm(path) {}
BreadthFirstSearch::~BreadthFirstSearch() {}
vector<Cell> BreadthFirstSearch::solve(Maze maze) {
    vector<Cell> v;
    Cell c(10, 20);
    v.push_back(c);
    return v;
}
