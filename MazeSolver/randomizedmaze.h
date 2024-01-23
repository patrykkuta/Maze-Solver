#ifndef RANDOMIZEDMAZE_H
#define RANDOMIZEDMAZE_H

#include "maze.h"
#include <random>
#include <set>

using namespace std;

class RandomizedMaze : public Maze
{
private:
    set<Cell*> frontier;
    random_device rd;

    Cell* randomStart();
    Cell* randomFinish();
    void generateMaze();
    void addUnvisitedNeighbours(Cell* cell);
    unsigned short randomFrontierPosition();
    void connect(Cell* cell);

public:
    RandomizedMaze(unsigned short width, unsigned short height, double complexity);
};

#endif // RANDOMIZEDMAZE_H
