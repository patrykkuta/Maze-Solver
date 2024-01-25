#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch() {}

DepthFirstSearch::~DepthFirstSearch() {}

void DepthFirstSearch::solve(Maze &maze) {

    for(vector<Cell*> col: maze.getMaze()) {
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

        steps.push(new Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze.getFinishCell()) {
            solutionPath = backtrace(path, maze.getStartCell(), maze.getFinishCell());
            break;
        }

        current->visit();

        Wall walls[] = {Wall::NONE, Wall::NONE, Wall::NONE, Wall::NONE};
        for (Wall wall: current->getWalls()) {
            if (wall == Wall::NORTH) {
                walls[0] = Wall::NORTH;
            }
            else if (wall == Wall::SOUTH) {
                walls[1] = Wall::SOUTH;
            }
            else if (wall == Wall::EAST) {
                walls[2] = Wall::EAST;
            }
            else if (wall == Wall::WEST) {
                walls[3] = Wall::WEST;
            }
        }

        // North
        if(walls[0] == Wall::NONE && !maze.getMaze()[current->getY() - 1][current->getX()]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY() - 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        // South
        if(walls[1] == Wall::NONE && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY() + 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        // East
        if(walls[2] == Wall::NONE && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY()][current->getX() + 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        // West
        if(walls[3] == Wall::NONE && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
            stack.push(maze.getMaze()[current->getY()][current->getX() - 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() - 1], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() - 1]));
        }
    }
}

vector<Cell*> DepthFirstSearch::backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell) {
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