#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include "pathfindingalgorithm.h"

class AStarSearch : public PathFindingAlgorithm
{
public:
    AStarSearch();
    ~AStarSearch();

    void solve(Maze &maze) override;

private:
    class Comparator {
    public:
        bool operator()(const pair<Cell*, int>& pair1, const pair<Cell*, int>& pair2) const {
            return pair1.second > pair2.second; // Compare the manhattan distance to finish cell
        }
    };

    unsigned int manhattanDistance(Cell* current, Cell* finishCell);
};

#endif // ASTARSEARCH_H
