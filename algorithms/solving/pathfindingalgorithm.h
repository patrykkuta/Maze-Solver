#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <vector>
#include <algorithm>
#include <queue>
#include "step.h"
#include "maze.h"
#include "Cell.h"
#include "algorithm.h"

/**
 * @class PathFindingAlgorithm
 * @brief Abstract class for pathfinding algorithms.
 */
class PathFindingAlgorithm : public Algorithm {
protected:
    vector<Cell*> solution; /**< Vector to store the solution path. */
    unordered_map<Cell*, Cell*> path; /**< Unordered map to store relationships between cells for path reconstruction. */
    Maze *maze; /**< Pointer to a maze to solve */

    /**
     * @brief Backtraces the solution path from the finish cell to the start cell.
     * @param path A map representing the Child cell - Parent cell relationships.
     * @param startCell The starting cell of the path.
     * @param finishCell The finishing cell of the path.
     * @return A vector of Cell pointers representing the backtraced path.
     */
    vector<Cell*> backtrace(unordered_map<Cell*, Cell*>& path, Cell* startCell, Cell* finishCell);

    virtual void addUnvisitedNeighbours(Cell* cell) = 0;

public:
    /**
     * @brief Constructor for the PathFindingAlgorithm class.
     */
    PathFindingAlgorithm();

    /**
     * @brief Destructor for the PathFindingAlgorithm class.
     */
    virtual ~PathFindingAlgorithm();

    /**
     * @brief Gets the solution path found by the algorithm.
     * @return A vector of Cell pointers representing the solution path.
     */
    vector<Cell*> getSolution();

    /**
     * @brief Abstract function to solve the maze.
     * @param maze The maze to be solved.
     */
    virtual void solve(Maze* maze) = 0;
};

#endif // PATHFINDINGALGORITHM_H
