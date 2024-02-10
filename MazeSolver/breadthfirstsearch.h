/**
 * @file breadthfirstsearch.h
 * @brief Header file for BreadthFirstSearch class, a derived class of PathFindingAlgorithm.
 */

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "pathfindingalgorithm.h"
#include <unordered_map>

/**
 * @class BreadthFirstSearch
 * @brief A class implementing the Breadth-First Search (BFS) algorithm for pathfinding in a maze.
 */
class BreadthFirstSearch : public PathFindingAlgorithm {
public:

    /**
     * @brief Default constructor for BreadthFirstSearch.
     */
    BreadthFirstSearch();

    /**
     * @brief Destructor for BreadthFirstSearch.
     */
    ~BreadthFirstSearch();

    /**
     * @brief Solves the given maze using the Breadth-First Search algorithm.
     * @param maze The maze to be solved.
     */
    void solve(Maze &maze) override;
};

#endif // BREADTHFIRSTSEARCH_H
