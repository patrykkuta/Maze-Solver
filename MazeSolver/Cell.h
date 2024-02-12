#ifndef CELL_H
#define CELL_H

#include "Wall.h"
#include <vector>
#include <map>

using namespace std;

/**
 * @class Cell
 * @brief Represents a cell in a grid used for maze generation and traversal.
 */
class Cell {
private:
    unsigned short x; /**< The x-coordinate of the cell. */
    unsigned short y; /**< The y-coordinate of the cell. */

    /**
     * @brief Mapping of walls and their existence status in the cell.
     * The keys are Wall enum values, and the values are booleans indicating whether the wall exists.
     */
    map<Wall, bool> walls = {
        {Wall::NORTH, true},
        {Wall::SOUTH, true},
        {Wall::WEST, true},
        {Wall::EAST, true}
    };

    bool visited = false; /**< Flag indicating whether the cell has been visited during maze traversal. */

public:
    /**
     * @brief Constructor for the Cell class.
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     */
    Cell(unsigned short x, unsigned short y);

    /**
     * @brief Getter function for the x-coordinate of the cell.
     * @return The x-coordinate of the cell.
     */
    unsigned short getX();

    /**
     * @brief Getter function for the y-coordinate of the cell.
     * @return The y-coordinate of the cell.
     */
    unsigned short getY();

    /**
     * @brief Removes the specified wall from the cell.
     * @param wall The wall to be removed (North, South, West, East).
     */
    void removeWall(Wall wall);

    /**
     * @brief Equality operator for comparing two cells.
     * @param other The other cell to compare with.
     * @return True if the cells have the same coordinates, false otherwise.
     */
    bool operator==(const Cell& other) const;

    /**
     * @brief Inequality operator for comparing two cells.
     * @param other The other cell to compare with.
     * @return True if the cells have different coordinates, false otherwise.
     */
    bool operator!=(const Cell& other) const;

    /**
     * @brief Marks the cell as visited.
     */
    void visit();

    /**
     * @brief Checks whether the cell has been visited.
     * @return True if the cell has been visited, false otherwise.
     */
    bool wasVisited();

    /**
     * @brief Resets the visited flag of the cell.
     */
    void resetVisited();

    /**
     * @brief Gets the walls and their existence status in the cell.
     * @return A map of walls and their existence status.
     */
    map<Wall, bool> getWalls();
};

#endif // CELL_H
