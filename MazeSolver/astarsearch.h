/**
 * @file astarsearch.h
 * @brief Header file for AStarSearch class, a derived class of PathFindingAlgorithm.
 */

#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include "pathfindingalgorithm.h"

/**
 * @class AStarSearch
 * @brief A class implementing the A* search algorithm for pathfinding in a maze.
 */
class AStarSearch : public PathFindingAlgorithm {
public:

    /**
     * @brief Default constructor for AStarSearch.
     */
    AStarSearch();

    /**
     * @brief Destructor for AStarSearch.
     */
    ~AStarSearch();

    /**
     * @brief Solves the given maze using the A* search algorithm.
     * @param maze The maze to be solved.
     */
    void solve(Maze &maze) override;

private:
    /**
     * @class Comparator
     * @brief A functor class used to define the comparison criteria for the priority queue.
     */
    class Comparator {
    public:
        /**
         * @brief Overloaded operator() to compare two pairs based on the second element in reverse order.
         * @param pair1 The first pair to compare.
         * @param pair2 The second pair to compare.
         * @return True if the second element of pair1 is greater than the second element of pair2.
         */
        bool operator()(const pair<Cell*, int>& pair1, const pair<Cell*, int>& pair2) const {
            return pair1.second > pair2.second; // Compare the Manhattan distance to the finish cell
        }
    };

    /**
     * @brief Calculates the Manhattan distance between two cells.
     * @param current The current cell.
     * @param finishCell The finish cell.
     * @return The Manhattan distance between the two cells.
     */
    unsigned int manhattanDistance(Cell* current, Cell* finishCell);
};

#endif // ASTARSEARCH_H
