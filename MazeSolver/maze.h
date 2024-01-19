#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <array>

using namespace std;

class Maze
{
private:
    int width = 16;
    int height = 16;
    double complexity = 0.2;
    vector<array<int, 2>> walls;
    vector<array<int, 2>> path;
    array<int, 2> startCoords;
    array<int, 2> finishCoords;

public:
    int getWidth();
    int getHeight();
    double getComplexity();
    vector<array<int, 2>> getPath;
    vector<array<int, 2>> getWalls;
};

#endif // MAZE_H
