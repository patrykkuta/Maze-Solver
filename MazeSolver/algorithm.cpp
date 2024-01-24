#include "algorithm.h"

Algorithm::Algorithm() {}

Algorithm::~Algorithm() {
    path.clear();
    visitedCells.clear();
}
bool Algorithm::addVisitedCell(Cell cell) {
    auto iterator = find(visitedCells.begin(), visitedCells.end(), cell);

    if (iterator == visitedCells.end()) {
        visitedCells.push_back(cell);
        return true;
    }

    return false;
}
