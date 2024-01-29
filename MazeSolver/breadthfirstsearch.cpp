#include "breadthfirstsearch.h"
#include <queue>

using namespace std;

BreadthFirstSearch::BreadthFirstSearch() {}

BreadthFirstSearch::~BreadthFirstSearch() {}

void BreadthFirstSearch::solve(Maze &maze) {

    for(vector<Cell*>& col: maze.getMaze()) {
        for (Cell* cell: col) {
            cell->resetVisited();
        }
    }

    queue<Cell*> q;
    unordered_map<Cell*, Cell*> path;

    q.push(maze.getStartCell());

    while (!q.empty()) {
        Cell* current = q.front();
        q.pop();

        steps.push(new Step(State::CURRENT, current));

        // Check if the current cell is the finish cell
        if (*current == *maze.getFinishCell()) {
            solutionPath = backtrace(path, maze.getStartCell(), maze.getFinishCell());
            break;
        }

        current->visit();

        map<Wall, bool> walls = current->getWalls();

        if(!walls[Wall::NORTH] && !maze.getMaze()[current->getY() - 1][current->getX()]->wasVisited()) {
            q.push(maze.getMaze()[current->getY() - 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        if(!walls[Wall::SOUTH] && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            q.push(maze.getMaze()[current->getY() + 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        if(!walls[Wall::EAST] && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            q.push(maze.getMaze()[current->getY()][current->getX() + 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        if(!walls[Wall::WEST] && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
            q.push(maze.getMaze()[current->getY()][current->getX() - 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() - 1], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() - 1]));
        }
    }
}

vector<Cell*> BreadthFirstSearch::backtrace(unordered_map<Cell*, Cell*> &path, Cell* startCell, Cell* finishCell) {
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
