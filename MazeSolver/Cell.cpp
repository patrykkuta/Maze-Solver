#include "Cell.h"

Cell::Cell(unsigned short x, unsigned short y) : x(x), y(y) {}

unsigned short Cell::getX() {return x;}

unsigned short Cell::getY() {return y;}

void Cell::removeWall(Wall wall) {
    walls[wall] = false;
}

bool Cell::operator==(const Cell& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

bool Cell::operator!=(const Cell& other) const {
    return (this->x != other.x) || (this->y != other.y);
}

void Cell::visit() {visited = true;}

bool Cell::wasVisited() {return visited;}

map<Wall, bool> Cell::getWalls() {
    return walls;
}

void Cell::resetVisited() {
    visited = false;
}
