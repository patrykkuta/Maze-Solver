#ifndef RANDOMIZEDMAZE_H
#define RANDOMIZEDMAZE_H

#include "maze.h"
#include <algorithm>
#include <random>
#include <set>

using namespace std;

class RandomizedMaze : public Maze
{
private:
    set<Cell*> frontier;
    random_device rd;

    Cell* getGenerationStartCell();
    void addUnvisitedNeighbours(Cell* cell);
    unsigned short randomFrontierPosition();
    bool connect(Cell* cell);


public:
    RandomizedMaze(unsigned short width, unsigned short height);
    ~RandomizedMaze();

    void generateMaze() override;
};

#endif // RANDOMIZEDMAZE_H
