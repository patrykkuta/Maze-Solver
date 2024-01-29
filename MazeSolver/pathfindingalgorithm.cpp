#include "pathfindingalgorithm.h"

PathFindingAlgorithm::PathFindingAlgorithm() {}

PathFindingAlgorithm::~PathFindingAlgorithm() {}

queue<Step*> PathFindingAlgorithm::getSolvingSteps() {
    return solvingSteps;
}

vector<Cell*> PathFindingAlgorithm::getSolution() {
    return solution;
}

vector<Cell*> PathFindingAlgorithm::backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell) {
    Cell* current = finishCell;
    vector<Cell*> backtracedPath;

    while (*current != *startCell) {
        if(path.find(current) != path.end()) {
            backtracedPath.push_back(path[current]);
            current = path[current];
        }
    }

    backtracedPath.pop_back(); // Remove starting cell

    return backtracedPath;
}
