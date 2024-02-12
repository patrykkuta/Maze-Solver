#ifndef RANDOMIZEDPRIMSALGORITHM_H
#define RANDOMIZEDPRIMSALGORITHM_H

#include "generatingalgorithm.h"
#include <random>
#include <algorithm>
#include <set>

/**
 * @class RandomizedPrimsAlgorithm
 * @brief Implementation of a randomized version of the Prim's algorithm for maze generation.
 */
class RandomizedPrimsAlgorithm : public GeneratingAlgorithm {
private:
    random_device rd; /**< Random device for generating random numbers. */
    set<Cell*> frontier; /**< Set of frontier cells for the generation process. */

    /**
     * @brief Generates a random position within the frontier.
     * @return An unsigned short representing the random position.
     */
    unsigned short randomFrontierPosition();

protected:
    Cell* getGenerationStartCell() override;

    /**
     * @brief Adds unvisited neighbours of a cell to the frontier.
     * @param cell The cell whose unvisited neighbours will be added to the frontier.
     */
    void addUnvisitedNeighbours(Cell* cell) override;

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
