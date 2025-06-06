#ifndef GENERATINGALGORITHM_H
#define GENERATINGALGORITHM_H

#include "Cell.h"
#include "algorithm.h"

/**
 * @class GeneratingAlgorithm
 * @brief Abstract class for maze generation algorithms.
 */
class GeneratingAlgorithm : public Algorithm {
protected:
    unsigned short mazeWidth; /**< The width of the maze. */
    unsigned short mazeHeight; /**< The height of the maze. */
    vector<vector<Cell*>> maze; /**< 2D vector representing the maze cells. */

    /**
     * @brief Gets the starting cell for maze generation.
     * @return A pointer to the starting cell for generation.
     */
    virtual Cell* getGenerationStartCell() = 0;

    /**
     * @brief Connects the given cell to a neighboring visited cell.
     * @param cell The cell to connect.
     * @return True if a connection was established, false otherwise.
     */
    bool connect(Cell* cell);

    void addUnvisitedNeighbours(Cell* cell) = 0;

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
};

#endif // GENERATINGALGORITHM_H
