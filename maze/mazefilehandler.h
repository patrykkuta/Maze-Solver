#ifndef MAZEFILEHANDLER_H
#define MAZEFILEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include "Cell.h"
#include "maze.h"

using namespace std;

/**
 * @class MazeFileHandler
 * @brief Handles maze file operations, such as saving a maze to a file.
 */
class MazeFileHandler {
public:
    /**
     * @brief Constructor for the MazeFileHandler class.
     * @param filePath The file path for the maze file.
     */
    MazeFileHandler(string filePath);

    /**
     * @brief Saves the maze to a file.
     * @param maze A pointer to the maze to be saved.
     * @return True if the save operation is successful, false otherwise.
     */
    bool saveMaze(Maze* maze);

private:
    string filePath; /**< The file path for the maze file. */
};

#endif // MAZEFILEHANDLER_H
