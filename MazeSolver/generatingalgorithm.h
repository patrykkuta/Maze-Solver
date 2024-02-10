/**
 * @file GeneratingAlgorithm.h
 * @brief Declaration of the GeneratingAlgorithm class, an abstract base class for maze generation algorithms.
 */
#ifndef GENERATINGALGORITHM_H
#define GENERATINGALGORITHM_H

#include "Cell.h"
#include "Step.h"
#include <set>

/**
 * @class GeneratingAlgorithm
 * @brief Abstract base class for maze generation algorithms.
 */
class GeneratingAlgorithm {
protected:
    unsigned short mazeWidth; /**< The width of the maze. */
    unsigned short mazeHeight; /**< The height of the maze. */
    vector<vector<Cell*>> maze; /**< 2D vector representing the maze cells. */
    set<Cell*> frontier; /**< Set of frontier cells for the generation process. */
    vector<Step> generationSteps; /**< Vector to store the steps taken during maze generation. */

    /**
     * @brief Abstract method to get the starting cell for maze generation.
     * @return A pointer to the starting cell for generation.
     */
    virtual Cell* getGenerationStartCell() = 0;

    /**
     * @brief Connects the given cell to a neighboring visited cell.
     * @param cell The cell to connect.
     * @return True if a connection was established, false otherwise.
     */
    bool connect(Cell* cell);

public:
    /**
     * @brief Constructor for the GeneratingAlgorithm class.
     * @param width The width of the maze.
     * @param height The height of the maze.
     */
    GeneratingAlgorithm(unsigned short width, unsigned short height);

    /**
     * @brief Destructor for the GeneratingAlgorithm class.
     */
    virtual ~GeneratingAlgorithm();

    /**
     * @brief Abstract method for generating a maze.
     * @return A 2D vector representing the generated maze.
     */
    virtual vector<vector<Cell*>> generate() = 0;

    /**
     * @brief Gets the generation steps taken during maze generation.
     * @return A vector of Step objects representing the generation steps.
     */
    vector<Step> getGenerationSteps();
};

#endif // GENERATINGALGORITHM_H
