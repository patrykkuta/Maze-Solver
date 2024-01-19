#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <array>
#include "maze.h"

using namespace std;

class Algorithm
{
private:
    vector<array<int, 2>> path;
    vector<array<int, 2>> visitedCoords;
public:
    Algorithm(vector<array<int, 2>> path);
    virtual ~Algorithm();

    virtual vector<array<int, 2>> solve(Maze maze) = 0;
    bool addVisitedCoords(array<int, 2> coords);
};

#endif // ALGORITHM_H
