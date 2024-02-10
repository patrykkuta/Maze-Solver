/**
 * @file AStarSearch.cpp
 * @brief Implementation of the AStarSearch class methods.
 */

#include "astarsearch.h"

AStarSearch::AStarSearch() {}

AStarSearch::~AStarSearch() {}

void AStarSearch::solve(Maze &maze) {

    for(vector<Cell*>& col: maze.getMaze()) {
        for (Cell* cell: col) {
            cell->resetVisited();
        }
    }

    priority_queue<pair<Cell*, int>, vector<pair<Cell*, int>>, Comparator> frontier;
    unordered_map<Cell*, Cell*> path;

    Cell* startCell = maze.getStartCell();
    Cell* finishCell = maze.getFinishCell();
    frontier.push(pair<Cell*, int>(startCell, manhattanDistance(startCell, finishCell)));

    while (!frontier.empty()) {
        Cell* current = frontier.top().first;
        frontier.pop();

        solvingSteps.push(new Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze.getFinishCell()) {
            solution = backtrace(path, maze.getStartCell(), maze.getFinishCell());
            break;
        }

        current->visit();

        map<Wall, bool> walls = current->getWalls();

        // North
        if(!walls[Wall::NORTH] && !maze.getMaze()[current->getY() - 1][current->getX()]->wasVisited()) {
            frontier.push(pair<Cell*, int>(maze.getMaze()[current->getY() - 1][current->getX()], manhattanDistance(maze.getMaze()[current->getY() - 1][current->getX()], finishCell)));
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        // South
        if(!walls[Wall::SOUTH] && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            frontier.push(pair<Cell*, int>(maze.getMaze()[current->getY() + 1][current->getX()], manhattanDistance(maze.getMaze()[current->getY() + 1][current->getX()], finishCell)));
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        // East
        if(!walls[Wall::EAST] && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            frontier.push(pair<Cell*, int>(maze.getMaze()[current->getY()][current->getX() + 1], manhattanDistance(maze.getMaze()[current->getY()][current->getX() + 1], finishCell)));
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        // West
        if(!walls[Wall::WEST] && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
            frontier.push(pair<Cell*, int>(maze.getMaze()[current->getY()][current->getX() - 1], manhattanDistance(maze.getMaze()[current->getY()][current->getX() - 1], finishCell)));
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() - 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() - 1]));
        }
    }
}

unsigned int AStarSearch::manhattanDistance(Cell* current, Cell* finishCell) {
    return (abs(current->getX() - finishCell->getX()) + abs(current->getY() - finishCell->getY()));
}

