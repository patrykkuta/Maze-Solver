#ifndef STATE_H
#define STATE_H

/**
 * @enum State
 * @brief Enumeration representing different cell states.
 */
enum State {
    NEIGHBOUR, /**< Neighbour/in-frontier state. */
    CURRENT,   /**< Current state. */
    SOLUTION   /**< Solution state. */
};

#endif // STATE_H
