#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch() {}

DepthFirstSearch::~DepthFirstSearch() {}

void DepthFirstSearch::solve(Maze &maze) {

    for(vector<Cell*>& col: maze.getMaze()) {
        for (Cell* cell: col) {
            cell->resetVisited();
        }
    }

    stack<Cell*> stack;
    unordered_map<Cell*, Cell*> path;

    stack.push(maze.getStartCell());

    while (!stack.empty()) {
        Cell* current = stack.top();
        stack.pop();

        solvingSteps.push(new Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze.getFinishCell()) {
            solution = backtrace(path, maze.getStartCell(), maze.getFinishCell());
            break;
        }

        current->visit();

        map<Wall, bool> walls = current->getWalls();

        if(!walls[Wall::NORTH] && !maze.getMaze()[current->getY() - 1][current->getX()]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY() - 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        if(!walls[Wall::SOUTH] && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY() + 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        if(!walls[Wall::EAST] && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY()][current->getX() + 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        if(!walls[Wall::WEST] && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY()][current->getX() - 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() - 1], current));
            solvingSteps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() - 1]));
        }
    }
}
