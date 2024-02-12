#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "pathfindingalgorithm.h"
#include <stack>

using namespace std;

/**
 * @class DepthFirstSearch
 * @brief A class implementing Depth-First Search (DFS) algorithm for pathfinding in a maze.
 */
class DepthFirstSearch : public PathFindingAlgorithm {
private:
    stack<Cell*> frontier; /**< Stack storing cells to be explored by the algorithm. */

protected:
    /**
     * @brief Adds unvisited neighbours of a cell to the frontier.
     * @param cell The cell whose unvisited neighbours will be added to the frontier.
     */
    void addUnvisitedNeighbours(Cell* cell) override;

public:
    /**
     * @brief Constructor for the DepthFirstSearch class.
     */
    DepthFirstSearch();

    /**
     * @brief Destructor for the DepthFirstSearch class.
     */
    ~DepthFirstSearch();

    /**
     * @brief Solves the given maze using Depth-First Search algorithm.
     * @param maze The maze to be solves.
     */
    void solve(Maze* maze) override;
};

#endif // DEPTHFIRSTSEARCH_H
