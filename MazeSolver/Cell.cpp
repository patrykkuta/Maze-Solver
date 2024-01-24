//
// Created by Patryk Kuta on 22/01/2024.
//

#include "Cell.h"

Cell::Cell(unsigned short x, unsigned short y) : x(x), y(y) {}

unsigned short Cell::getX() {return x;}

unsigned short Cell::getY() {return y;}

void Cell::removeWall(Wall wall) {
    if (wall == Wall::NORTH) {
        walls.NORTH = false;
    }
    else if (wall == Wall::SOUTH) {
        walls.SOUTH = false;
    }
    else if (wall == Wall::EAST) {
        walls.EAST = false;
    }
    else if (wall == Wall::WEST){
        walls.WEST = false;
    }
}

bool Cell::operator==(const Cell& other) const {
    return (x == other.x) && (y == other.y);
}

bool Cell::operator!=(const Cell& other) const {
    return (x != other.x) || (y != other.y);
}

void Cell::visit() {visited = true;}

bool Cell::wasVisited() {return visited;}

vector<Wall> Cell::getWalls() {
    vector<Wall> w;

    if(walls.NORTH) {
        w.push_back(Wall::NORTH);
    }
    if(walls.SOUTH) {
        w.push_back(Wall::SOUTH);
    }
    if(walls.WEST) {
        w.push_back(Wall::WEST);
    }
    if(walls.EAST) {
        w.push_back(Wall::EAST);
    }

    return w;
}

void Cell::resetVisited() {
    visited = false;
}
