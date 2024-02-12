#ifndef CUSTOMMAZE_H
#define CUSTOMMAZE_H

#include "maze.h"
#include <string>

using namespace std;

/**
 * @class CustomMaze
 * @brief Represents a custom maze loaded from a file, inheriting from the Maze class.
 */
class CustomMaze : public Maze {
private:
    string filePath; /**< The file path to load the custom maze. */

    /**
     * @brief Generates the custom maze by reading data from the specified file.
     *
     * Reads maze dimensions, cell information, and walls from the file.
     * Constructs the maze and sets the start and finish cells.
     */
    void generateMaze() override;

public:
    /**
     * @brief Constructor for the CustomMaze class.
     * @param filePath The file path to load the custom maze.
     */
    CustomMaze(string filePath);
};

#endif // CUSTOMMAZE_H
