/**
 * @file Maze.h
 * @brief Declaration of the Maze class, an abstract base class for maze representations.
 */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <queue>
#include "step.h"
#include "Cell.h"
#include "generatingalgorithm.h"

using namespace std;

/**
 * @class Maze
 * @brief Represents an abstract base class for maze representations.
 */
class Maze {
protected:
    unsigned short width; /**< The width of the maze. */
    unsigned short height; /**< The height of the maze. */
    vector<vector<Cell*>> maze; /**< 2D vector representing the maze cells. */
    Cell* startCell; /**< Pointer to the starting cell of the maze. */
    Cell* finishCell; /**< Pointer to the finishing cell of the maze. */
    GeneratingAlgorithm* generatingAlgorithm; /**< Pointer to the maze generation algorithm. */

public:
    /**
     * @brief Default constructor for the Maze class.
     */
    Maze();

    /**
     * @brief Constructor for the Maze class with specified width, height, and generating algorithm.
     * @param width The width of the maze.
     * @param height The height of the maze.
     * @param algorithm The generating algorithm used to create the maze.
     */
    Maze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm);

    /**
     * @brief Destructor for the Maze class.
     */
    virtual ~Maze();

    /**
     * @brief Gets the width of the maze.
     * @return The width of the maze.
     */
    unsigned short getWidth();

    /**
     * @brief Gets the height of the maze.
     * @return The height of the maze.
     */
    unsigned short getHeight();

    /**
     * @brief Gets the 2D vector representing the maze cells.
     * @return A 2D vector representing the maze cells.
     */
    vector<vector<Cell*>> getMaze();

    /**
     * @brief Gets the starting cell of the maze.
     * @return A pointer to the starting cell of the maze.
     */
    Cell* getStartCell();

    /**
     * @brief Gets the finishing cell of the maze.
     * @return A pointer to the finishing cell of the maze.
     */
    Cell* getFinishCell();

    /**
     * @brief Gets the generating algorithm used to create the maze.
     * @return A pointer to the maze generation algorithm.
     */
    GeneratingAlgorithm* getGeneratingAlgorithm();

    /**
     * @brief Abstract function to generate the maze.
     */
    virtual void generateMaze() = 0;
};

#endif // MAZE_H
