#include "maze.h"
#include <iostream>

Maze::Maze() {}

Maze::Maze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm) :
    width(width),
    height(height),
    generatingAlgorithm(algorithm) {}

Maze::~Maze() {
    for (unsigned short y = 0; y < height; y++) {
        for (unsigned short x = 0; x < width; x++) {
            delete maze[x][y];
        }
    }

    delete generatingAlgorithm;
}

unsigned short Maze::getWidth() {return width;}

unsigned short Maze::getHeight() {return height;}

vector<vector<Cell*>> Maze::getMaze() {return maze;}

Cell* Maze::getStartCell() {return startCell;}

Cell* Maze::getFinishCell() {return finishCell;}

GeneratingAlgorithm* Maze::getGeneratingAlgorithm() {return generatingAlgorithm;}
