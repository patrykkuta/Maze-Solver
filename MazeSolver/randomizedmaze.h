#ifndef RANDOMIZEDMAZE_H
#define RANDOMIZEDMAZE_H

#include "maze.h"

using namespace std;

class RandomizedMaze : public Maze
{
public:
    RandomizedMaze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm);
    ~RandomizedMaze();

    void generateMaze() override;
};

#endif // RANDOMIZEDMAZE_H
