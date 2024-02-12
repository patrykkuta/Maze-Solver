#include "generatingalgorithm.h"

GeneratingAlgorithm::GeneratingAlgorithm(unsigned short width, unsigned short height) : mazeWidth(width), mazeHeight(height) {
    // Initialize the maze with cells and all walls present
    for (unsigned short y = 0; y < mazeHeight; y++) {
        maze.emplace_back();

        for (unsigned short x = 0; x < mazeWidth; x++) {
            maze[y].emplace_back(new Cell(x, y));
        }
    }
}

GeneratingAlgorithm::~GeneratingAlgorithm() {}

bool GeneratingAlgorithm::connect(Cell* cell) {
    // Remove an appropriate wall if the neighbouring cell was visited
    if (cell->getY() < mazeHeight - 1 && maze[cell->getY() + 1][cell->getX()]->wasVisited()) {
        cell->removeWall(Wall::SOUTH);
        maze[cell->getY() + 1][cell->getX()]->removeWall(Wall::NORTH);
        return true;
    } else if (cell->getX() > 0 && maze[cell->getY()][cell->getX() - 1]->wasVisited()) {
        cell->removeWall(Wall::WEST);
        maze[cell->getY()][cell->getX() - 1]->removeWall(Wall::EAST);
        return true;
    } else if (cell->getX() < mazeWidth - 1 && maze[cell->getY()][cell->getX() + 1]->wasVisited()) {
        cell->removeWall(Wall::EAST);
        maze[cell->getY()][cell->getX() + 1]->removeWall(Wall::WEST);
        return true;
    } else if ((cell->getY() > 0) && maze[cell->getY() - 1][cell->getX()]->wasVisited()) {
        cell->removeWall(Wall::NORTH);
        maze[cell->getY() - 1][cell->getX()]->removeWall(Wall::SOUTH);
        return true;
    }
    return false;
}


