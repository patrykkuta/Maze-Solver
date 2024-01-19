#ifndef RANDOMIZEDMAZE_H
#define RANDOMIZEDMAZE_H

#include "maze.h"

class RandomizedMaze : public Maze
{
private:
    int randomWidth();
    int randomHeight();
    double randomComplexity();
    vector<array<int, 2>> randomWalls();
    vector<array<int, 2>> randomPath();
    array<int, 2> randomStart();
    array<int, 2> randomFinish();
public:
    RandomizedMaze();
};

#endif // RANDOMIZEDMAZE_H
