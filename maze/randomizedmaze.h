#ifndef RANDOMIZEDMAZE_H
#define RANDOMIZEDMAZE_H

#include "maze.h"

/**
 * @class RandomizedMaze
 * @brief A random maze generated using a maze generation algorithm.
 */
class RandomizedMaze : public Maze {
public:
    /**
     * @brief Constructor for the RandomizedMaze class.
     * @param width The width of the maze to be generated.
     * @param height The height of the maze to be generated.
     * @param algorithm The generating algorithm to be used.
     */
    RandomizedMaze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm);

    /**
     * @brief Generates the maze using the maze generation algorithm specified by the Maze class generationAlgorithm member.
     */
    void generateMaze() override;
};

#endif // RANDOMIZEDMAZE_H
