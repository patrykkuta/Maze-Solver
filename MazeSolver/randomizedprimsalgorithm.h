/**
 * @file RandomizedPrimsAlgorithm.h
 * @brief Declaration of the RandomizedPrimsAlgorithm class, an implementation of a randomized version of the Prim's algorithm for maze generation.
 */
#ifndef RANDOMIZEDPRIMSALGORITHM_H
#define RANDOMIZEDPRIMSALGORITHM_H

#include "generatingalgorithm.h"
#include <random>
#include <algorithm>

/**
 * @class RandomizedPrimsAlgorithm
 * @brief Implementation of a randomized version of the Prim's algorithm for maze generation.
 */
class RandomizedPrimsAlgorithm : public GeneratingAlgorithm {
private:
    random_device rd; /**< Random device for generating random numbers. */

    /**
     * @brief Generates a random position within the frontier.
     * @return An unsigned short representing the random position.
     */
    unsigned short randomFrontierPosition();

    /**
     * @brief Adds unvisited neighbours of a cell to the frontier.
     * @param cell The cell whose unvisited neighbours will be added to the frontier.
     */
    void addUnvisitedNeighbours(Cell* cell);

protected:
    /**
     * @brief Gets the starting cell for maze generation.
     * @return A pointer to the starting cell.
     */
    Cell* getGenerationStartCell() override;

public:
    /**
     * @brief Constructor for the RandomizedPrimsAlgorithm class.
     * @param width The width of the maze to be generated.
     * @param height The height of the maze to be generated.
     */
    RandomizedPrimsAlgorithm(unsigned short width, unsigned short height);

    /**
     * @brief Destructor for the RandomizedPrimsAlgorithm class.
     */
    ~RandomizedPrimsAlgorithm();

    /**
     * @brief Generates a maze using a randomized version of the Prim's algorithm.
     * @return A 2D vector of Cell pointers representing the generated maze.
     */
    vector<vector<Cell*>> generate() override;
};

#endif // RANDOMIZEDPRIMSALGORITHM_H
