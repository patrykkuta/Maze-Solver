/**
 * @file Step.h
 * @brief Declaration of the Step class representing a step in maze algorithms.
 */
#ifndef STEP_H
#define STEP_H

#include "state.h"
#include "Cell.h"

/**
 * @class Step
 * @brief Represents a step in maze algorithms.
 */
class Step {
public:
    /**
     * @brief Constructor for the Step class.
     * @param state The state of the step.
     * @param cell A pointer to the cell associated with the step.
     */
    Step(State state, Cell* cell);

    /**
     * @brief Gets the state of the step.
     * @return The state of the step.
     */
    State state();

    /**
     * @brief Gets a pointer to the cell associated with the step.
     * @return The pointer to the cell associated with the step.
     */
    Cell* cell();

    /**
     * @brief Checks if two steps are equal.
     * @param other The step to compare with.
     * @return True if the steps are equal, false otherwise.
     */
    bool operator==(const Step& other) const;

private:
    pair<State, Cell*> step; /**< Pair representing the state and cell of the step. */
};

#endif // STEP_H
