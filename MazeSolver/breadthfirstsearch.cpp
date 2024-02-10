/**
 * @file BreadthFirstSearch.cpp
 * @brief Implementation of the BreadthFirstSearch class methods.
 */

#include "breadthfirstsearch.h"
#include <queue>

using namespace std;

BreadthFirstSearch::BreadthFirstSearch() {}

BreadthFirstSearch::~BreadthFirstSearch() {}

void BreadthFirstSearch::solve(Maze &maze) {
    // Reset the visited state of all cells in the maze
    for (vector<Cell*>& col : maze.getMaze()) {
        for (Cell* cell : col) {
            cell->resetVisited();
        }
    }

    // Initialize a frontier (queue), and a path for backtracking
    queue<Cell*> frontier;
    unordered_map<Cell*, Cell*> path;

    // Start BFS from the start cell
    frontier.push(maze.getStartCell());

    while (!frontier.empty()) {
        Cell* current = frontier.front();
        frontier.pop();

        solvingSteps.push(new Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze.getFinishCell()) {
            solution = backtrace(path, maze.getStartCell(), maze.getFinishCell());
            break;
        }

        current->visit();

        map<Wall, bool> walls = current->getWalls();

        // Explore neighboring cells and update the path
        if (!walls[Wall::NORTH] && !maze.getMaze()[current->getY() - 1][current->getX()]->wasVisited()) {
            frontier.push(maze.getMaze()[current->getY() - 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        if (!walls[Wall::SOUTH] && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            frontier.push(maze.getMaze()[current->getY() + 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        if (!walls[Wall::EAST] && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            frontier.push(maze.getMaze()[current->getY()][current->getX() + 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        if (!walls[Wall::WEST] && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
            frontier.push(maze.getMaze()[current->getY()][current->getX() - 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() - 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() - 1]));
        }
    }
}
