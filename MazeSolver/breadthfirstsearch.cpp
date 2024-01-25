#include "breadthfirstsearch.h"
#include <queue>
#include <set>

using namespace std;

BreadthFirstSearch::BreadthFirstSearch(Maze &maze) {
    solve(maze);
}

BreadthFirstSearch::~BreadthFirstSearch() {}

void BreadthFirstSearch::solve(Maze &maze) {

    for(vector<Cell*> col: maze.getMaze()) {
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
            q.push(maze.getMaze()[current->getY() - 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() - 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() - 1][current->getX()]));
        }

        // South
        if(walls[1] == Wall::NONE && !maze.getMaze()[current->getY() + 1][current->getX()]->wasVisited()) {
            q.push(maze.getMaze()[current->getY() + 1][current->getX()]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY() + 1][current->getX()], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY() + 1][current->getX()]));
        }

        // East
        if(walls[2] == Wall::NONE && !maze.getMaze()[current->getY()][current->getX() + 1]->wasVisited()) {
            q.push(maze.getMaze()[current->getY()][current->getX() + 1]);
            path.insert(pair<Cell*, Cell*>(maze.getMaze()[current->getY()][current->getX() + 1], current));
            steps.push(new Step(State::NEIGHBOUR, maze.getMaze()[current->getY()][current->getX() + 1]));
        }

        // West
        if(walls[3] == Wall::NONE && !maze.getMaze()[current->getY()][current->getX() - 1]->wasVisited()) {
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
