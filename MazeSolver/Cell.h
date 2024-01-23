//
// Created by Patryk Kuta on 22/01/2024.
//

#ifndef MAZESOLVER_CELL_H
#define MAZESOLVER_CELL_H

#include "Wall.cpp"
#include <vector>

using namespace std;

class Cell {
private:
    unsigned short x, y;

    bool visited = false;
public:
    Cell(unsigned short x, unsigned short y);
    unsigned short getX();
    unsigned short getY();
    void removeWall(Wall wall);
    bool operator==(const Cell& other) const;
    void visit();
    bool wasVisited();
    vector<Wall> getWalls();
    struct wall {
        bool NORTH = true;
        bool SOUTH = true;
        bool WEST = true;
        bool EAST = true;
    } walls;
};


#endif //MAZESOLVER_CELL_H
