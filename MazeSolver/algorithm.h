#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Step.h"
#include "Cell.h"

/**
 * @class Algorithm
 * @brief Abstract class for algorithms.
 */
class Algorithm
{
protected:
    vector<Step> steps; /**< Vector to store the steps of algorithm execution. */

    /**
     * @brief Adds unvisited neighbours of a cell to the frontier.
     * @param cell The cell whose unvisited neighbours will be added to the frontier.
     */
    virtual void addUnvisitedNeighbours(Cell* cell) = 0;

public:
    /**
     * @brief Gets the steps of algorithm execution.
     * @return A queue of Step objects representing the steps.
     */
    vector<Step>* getSteps();
};

#endif // ALGORITHM_H
