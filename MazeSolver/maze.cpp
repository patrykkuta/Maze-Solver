/**
 * @file Maze.cpp
 * @brief Implementation of the Maze class methods.
 */

#include "maze.h"

Maze::Maze() {}

Maze::Maze(unsigned short width, unsigned short height, GeneratingAlgorithm* algorithm) :
    width(width),
    height(height),
    generatingAlgorithm(algorithm) {}

Maze::~Maze() {
    maze.clear();
    delete startCell;
    delete finishCell;
}

unsigned short Maze::getWidth() {return width;}

unsigned short Maze::getHeight() {return height;}

vector<vector<Cell*>> Maze::getMaze() {return maze;}

Cell* Maze::getStartCell() {return startCell;}

Cell* Maze::getFinishCell() {return finishCell;}

GeneratingAlgorithm* Maze::getGeneratingAlgorithm() {return generatingAlgorithm;}
