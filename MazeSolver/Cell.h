//
// Created by Patryk Kuta on 22/01/2024.
//

#ifndef MAZESOLVER_CELL_H
#define MAZESOLVER_CELL_H

#include "Wall.cpp"
#include <vector>
#include <map>

using namespace std;

class Cell {
private:
    unsigned short x, y;
    map<Wall, bool> walls = {{Wall::NORTH, true},
                             {Wall::SOUTH, true},
                             {Wall::WEST, true},
                             {Wall::EAST, true}};

    bool visited = false;
public:
    Cell(unsigned short x, unsigned short y);
    unsigned short getX();
    unsigned short getY();
    void removeWall(Wall wall);
    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;
    void visit();
    bool wasVisited();
    void resetVisited();
    map<Wall, bool> getWalls();
};


#endif //MAZESOLVER_CELL_H
