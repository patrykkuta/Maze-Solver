/**
 * @file DepthFirstSearch.h
 * @brief Declaration of the DepthFirstSearch class, a pathfinding algorithm based on Depth-First Search.
 */
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
    void solve(Maze &maze) override;
};

#endif // DEPTHFIRSTSEARCH_H
