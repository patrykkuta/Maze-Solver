#include "astarsearch.h"

AStarSearch::AStarSearch() {}

AStarSearch::~AStarSearch() {}

void AStarSearch::solve(Maze* maze) {

    this->maze = maze;

    for(vector<Cell*>& col: maze->getMaze()) {
        for (Cell* cell: col) {
            cell->resetVisited();
        }
    }

    startCell = maze->getStartCell();
    finishCell = maze->getFinishCell();
    frontier.push(pair<Cell*, int>(startCell, manhattanDistance(startCell, finishCell)));

    while (!frontier.empty()) {
        Cell* current = frontier.top().first;
        frontier.pop();

        steps.push_back(Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze->getFinishCell()) {
            solution = backtrace(path, maze->getStartCell(), maze->getFinishCell());
            break;
        }

        current->visit();

        addUnvisitedNeighbours(current);
    }
}

unsigned int AStarSearch::manhattanDistance(Cell* current, Cell* finishCell) {
    return (abs(current->getX() - finishCell->getX()) + abs(current->getY() - finishCell->getY()));
}

void AStarSearch::addUnvisitedNeighbours(Cell* cell) {
    map<Wall, bool> walls = cell->getWalls();

    // North
    if(!walls[Wall::NORTH] && !maze->getMaze()[cell->getY() - 1][cell->getX()]->wasVisited()) {
        frontier.push(pair<Cell*, int>(maze->getMaze()[cell->getY() - 1][cell->getX()], manhattanDistance(maze->getMaze()[cell->getY() - 1][cell->getX()], finishCell)));
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY() - 1][cell->getX()], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY() - 1][cell->getX()]));
    }

    // South
    if(!walls[Wall::SOUTH] && !maze->getMaze()[cell->getY() + 1][cell->getX()]->wasVisited()) {
        frontier.push(pair<Cell*, int>(maze->getMaze()[cell->getY() + 1][cell->getX()], manhattanDistance(maze->getMaze()[cell->getY() + 1][cell->getX()], finishCell)));
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY() + 1][cell->getX()], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY() + 1][cell->getX()]));
    }

    // East
    if(!walls[Wall::EAST] && !maze->getMaze()[cell->getY()][cell->getX() + 1]->wasVisited()) {
        frontier.push(pair<Cell*, int>(maze->getMaze()[cell->getY()][cell->getX() + 1], manhattanDistance(maze->getMaze()[cell->getY()][cell->getX() + 1], finishCell)));
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY()][cell->getX() + 1], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY()][cell->getX() + 1]));
    }

    // West
    if(!walls[Wall::WEST] && !maze->getMaze()[cell->getY()][cell->getX() - 1]->wasVisited()) {
        frontier.push(pair<Cell*, int>(maze->getMaze()[cell->getY()][cell->getX() - 1], manhattanDistance(maze->getMaze()[cell->getY()][cell->getX() - 1], finishCell)));
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY()][cell->getX() - 1], cell));
        getSteps()->push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY()][cell->getX() - 1]));
    }
}

