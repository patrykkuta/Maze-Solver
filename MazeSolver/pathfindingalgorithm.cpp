#include "pathfindingalgorithm.h"

PathFindingAlgorithm::PathFindingAlgorithm() {}

PathFindingAlgorithm::~PathFindingAlgorithm() {}

vector<Cell*> PathFindingAlgorithm::getSolution() {
    return solution;
}

vector<Cell*> PathFindingAlgorithm::backtrace(unordered_map<Cell*, Cell*>& path, Cell* startCell, Cell* finishCell) {
    Cell* current = finishCell;
    vector<Cell*> backtracedPath;

    backtracedPath.push_back(current); // Add finish cell to the path

    // Add cell parent to the backtraced path until start cell reached
    while (*current != *startCell) {
        if (path.find(current) != path.end()) {
            backtracedPath.push_back(path[current]);
            current = path[current];
        }
    }

    return backtracedPath;
}
