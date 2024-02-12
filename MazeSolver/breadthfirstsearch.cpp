#include "breadthfirstsearch.h"
#include <queue>

using namespace std;

BreadthFirstSearch::BreadthFirstSearch() {}

BreadthFirstSearch::~BreadthFirstSearch() {}

void BreadthFirstSearch::solve(Maze* maze) {

    this->maze = maze;

    // Reset the visited state of all cells in the maze
    for (vector<Cell*>& col : maze->getMaze()) {
        for (Cell* cell : col) {
            cell->resetVisited();
        }
    }

    // Start BFS from the start cell
    frontier.push(maze->getStartCell());

    while (!frontier.empty()) {
        Cell* current = frontier.front();
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

void BreadthFirstSearch::addUnvisitedNeighbours(Cell* cell) {
    map<Wall, bool> walls = cell->getWalls();

    // Explore neighboring cells and update the path
    if (!walls[Wall::NORTH] && !maze->getMaze()[cell->getY() - 1][cell->getX()]->wasVisited()) {
        frontier.push(maze->getMaze()[cell->getY() - 1][cell->getX()]);
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY() - 1][cell->getX()], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY() - 1][cell->getX()]));
    }

    if (!walls[Wall::SOUTH] && !maze->getMaze()[cell->getY() + 1][cell->getX()]->wasVisited()) {
        frontier.push(maze->getMaze()[cell->getY() + 1][cell->getX()]);
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY() + 1][cell->getX()], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY() + 1][cell->getX()]));
    }

    if (!walls[Wall::EAST] && !maze->getMaze()[cell->getY()][cell->getX() + 1]->wasVisited()) {
        frontier.push(maze->getMaze()[cell->getY()][cell->getX() + 1]);
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY()][cell->getX() + 1], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY()][cell->getX() + 1]));
    }

    if (!walls[Wall::WEST] && !maze->getMaze()[cell->getY()][cell->getX() - 1]->wasVisited()) {
        frontier.push(maze->getMaze()[cell->getY()][cell->getX() - 1]);
        path.insert(pair<Cell*, Cell*>(maze->getMaze()[cell->getY()][cell->getX() - 1], cell));
        steps.push_back(Step(State::NEIGHBOUR, maze->getMaze()[cell->getY()][cell->getX() - 1]));
    }
}
