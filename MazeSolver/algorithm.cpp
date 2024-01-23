#include "algorithm.h"

Algorithm::Algorithm(vector<Cell> path) : path(path) {}
Algorithm::~Algorithm() {
    path.clear();
    visitedCells.clear();
}
bool Algorithm::addVisitedCell(Cell cell) {
    auto iterator = find(visitedCells.begin(), visitedCells.end(), cell);

    if (iterator == visitedCells.end()) {
        visitedCells.push_back(cell);
    }
}
